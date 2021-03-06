#include "Webserv.hpp"

Wevserv::Wevserv(Config& c) : c_(c), maxFd_(0)
{
  setupServers();
  fetchAllCGIExtensionsFromConfig();
  for (int i = 0; i < MAX_SESSION; i++)
  {
    responses_[i] = NULL;
    clients_[i].gc.setDebugLevel(c.getDebugLevel());
    clients_[i].hmp.setCgiScripts(cgiScripts_);
  }
  struct timeval tvForSelect;
  struct timeval nowTv;
  unsigned long mainLoopCounter = 0;
  while (1)
  {
    if (c.getDebugLevel() >= 1)
      std::cout << "[DEBUG]Loop : " << mainLoopCounter++ << "time" << std::endl;
    gettimeofday(&nowTv, NULL);
    for (int i = 0; i < MAX_SESSION; i++)
    {
      if (clients_[i].socketFd != -1)
      {
        if (nowTv.tv_sec - clients_[i].lastTvForClient.tv_sec > SESSION_TIMEOUT)
        {
          if (c.getDebugLevel() >= 1)
            std::cout << "[DEBUG]clients_[" << i << "] session timeout." << std::endl;
          clients_[i].initClient();
        }
      }
    }
    initFD();
    tvForSelect.tv_sec = SELECT_TIMEOUT;
    tvForSelect.tv_usec = 0;   
    if (select(maxFd_, &readFds_, &writeFds_, NULL, &tvForSelect) == -1)
      std::cout << "[EMERG]select() failed.(" << strerror(errno) << ")" << std::endl;
    for (std::vector<Socket>::iterator itrServer = servers_.begin();
      itrServer != servers_.end();
      itrServer++)
    {
      if (FD_ISSET(itrServer->get_listenfd(), &readFds_))
      {
        struct sockaddr_in clienSockaddrIn;
        socklen_t clienSockaddrInLen = sizeof(clienSockaddrIn);
        int acceptFd = accept(itrServer->get_listenfd(), \
                              (struct sockaddr*)&clienSockaddrIn, \
                              &clienSockaddrInLen);
        if (acceptFd == -1)
        {
          std::cout << "[EMERG]accept() failed." << std::endl;
          continue;
        }
        int r = fcntl(acceptFd, F_SETFL, O_NONBLOCK);
        if (r == -1)
        {
          std::cout << "[EMERG]fcntl() failed." << std::endl;
          close(acceptFd);
          continue;
        }
        if (c.getDebugLevel() >= 1)
          std::cout << "[DEBUG]accept[to " << itrServer->get_host() << ":" << itrServer->get_port() << " from " << ft_inet_ntos(clienSockaddrIn.sin_addr) << "]" << std::endl;
        bool limitOver = false;
        int limitOverI;
        for (int i = 0; i < MAX_SESSION; i++)
        {
          if (clients_[i].socketFd == -1)
          {
            clients_[i].socketFd = acceptFd;
            clients_[i].receivedData.setFd(clients_[i].socketFd);
            clients_[i].sc.setFd(clients_[i].socketFd);
            clients_[i].port = itrServer->get_port();
            clients_[i].host = itrServer->get_host();
            clients_[i].ip = ft_inet_ntos(clienSockaddrIn.sin_addr);
            clients_[i].lastTvForClient.tv_sec = nowTv.tv_sec;
            if (i > SESSION_LIMIT - 1)
            {
              limitOverI = i;
              limitOver = true;
            }
            break;
          }
        }
        if (limitOver)
        {
          std::cout << "[EMERG]over MAX_SESSION." << std::endl;
          responseNot200(limitOverI, 503);
        }
      }
    }
    for (int i = 0; i < MAX_SESSION; i++) {
      if(clients_[i].socketFd == -1)
        continue;
      if (FD_ISSET(clients_[i].socketFd, &readFds_))
      {
        if (!clients_[i].receivedData.recvFromSocket())
        {
          deleteResponses(i);
          clients_[i].initClient();
          continue;
        }
        debugPrintGetRecvData(i);
      }
      if (clients_[i].readFd != -1 && FD_ISSET(clients_[i].readFd, &readFds_))
      {
        if (!clients_[i].readDataFromFd.readFromFd())
        {
          if (responses_[i]->isCGI == true)
          {
            deleteResponses(i);
            responseNot200(i, 500);
          }
          else
          {
            deleteResponses(i);
            clients_[i].initClient();
          }
          continue;
        }
        debugPrintGetReadData(i);
      }
      if (clients_[i].status == PARSE_STARTLINE)
      {
        if (clients_[i].receivedData.cutOutRecvDataToEol() \
          && clients_[i].receivedData.getExtractedData() != "")
        {
          clients_[i].lastTvForClient.tv_sec = nowTv.tv_sec;
          debugPrintExtractedData(i);
          int code = clients_[i].hmp.parseRequestLine(clients_[i].receivedData.getExtractedData());
          if (code != 200)
            responseNot200(i, code);
          else if (clients_[i].hmp.parseRequestTarget(clients_[i].hmp.getRequestTarget()))
          {
            debugPrintStartLine(i);
            if (clients_[i].hmp.query_.size() > httpMessageParser::MAX_QUERY_SIZE)
              responseNot200(i, 414);
            else
              clients_[i].status = PARSE_HEADER;
          }
          else
            responseNot200(i, 400);
        }
      }
      if (clients_[i].status == PARSE_HEADER)
      {
        while (clients_[i].receivedData.cutOutRecvDataToEol())
        {
          if (clients_[i].receivedData.getExtractedData() == "")
          {
            debugPrintHeaders(i);
            std::map<std::string, std::string> headers = clients_[i].hmp.getHeaders();
            int code = clients_[i].hmp.isInvalidHeader();
            if (code != 200)
            {
              responseNot200(i, code);
              break;
            }
            if (clients_[i].isNeedBody(headers))
            {
              clients_[i].status = RESV_BODY;
              debugPrintGetRecvData(i);
            }
            else
              clients_[i].status = CREATE_RESPONSE;
            break;
          }
          else
          {
            if (clients_[i].hmp.isIllegalValueOfHostHeader(clients_[i].receivedData.getExtractedData())
              || clients_[i].hmp.parseHeader(clients_[i].receivedData.getExtractedData()) == 400)
            {
              responseNot200(i, 400);
              break;
            }
          }
        }
      }
      if (clients_[i].status == RESV_BODY && clients_[i].bChunked == false)
      {
        if (clients_[i].receivedData.cutOutRecvDataBySpecifyingBytes(ft_stoi(clients_[i].hmp.headers_["content-length"])))
        {
          clients_[i].body = clients_[i].receivedData.getExtractedData();
          debugPrintRequestBody(i);
          clients_[i].status = CREATE_RESPONSE;
        }
        else
          continue;
      }
      if (clients_[i].status == RESV_BODY && clients_[i].bChunked == true)
      {
        clients_[i].gc.setRecvData(&clients_[i].receivedData);
        clients_[i].gc.setClientBody(&clients_[i].body);
        int code = clients_[i].gc.parseChunkedData();
        if (code == -1)
          continue;
        if (code == 200)
        {
          debugPrintRequestBody(i);
          clients_[i].status = PARSE_HEADER_AFTER_CHUNKD;
        }
        else if (code == 400)
        {
          responseNot200(i, code);
        }
      }
      if (clients_[i].status == PARSE_HEADER_AFTER_CHUNKD)
      {
        while (clients_[i].receivedData.cutOutRecvDataToEol())
        {
          if (clients_[i].receivedData.getExtractedData() == "")
          {
            debugPrintHeaders(i);
            int code = clients_[i].hmp.isInvalidHeaderValue();
            if (code != 200)
              responseNot200(i, code);
            clients_[i].status = CREATE_RESPONSE;
            break;
          }
          else
          {
            if (clients_[i].hmp.isIllegalValueOfHostHeader(clients_[i].receivedData.getExtractedData())
              || clients_[i].hmp.parseHeader(clients_[i].receivedData.getExtractedData()) == 400)
            {
              responseNot200(i, 400);
              break;
            }
          }
        }
      }
      if (clients_[i].status == CREATE_RESPONSE)
      {
        responses_[i] = new Response(clients_[i], c);
        debugPrintResponceData(i);
        clients_[i].responseCode = responses_[i]->ResponseStatus;
        if (clients_[i].status == READWRITE)
        {
          // CGI?????????????????????
          clients_[i].writeFd = responses_[i]->getCgiFdForWrite();
          if (clients_[i].writeFd == -1)
          {
            deleteResponses(i);
            responseNot200(i, 500);
          }
          else
          {
            clients_[i].wc.setFd(clients_[i].writeFd);
            clients_[i].wc.setSendData(const_cast<char *>(clients_[i].body.c_str()), clients_[i].body.size());
          }
          // CGI???????????????????????????????????????
          clients_[i].readFd = responses_[i]->getCgiFd();
         if (clients_[i].readFd == -1)
          {
            close(clients_[i].writeFd);
            deleteResponses(i);
            responseNot200(i, 500);
          }
          else
            clients_[i].readDataFromFd.setFd(clients_[i].readFd);
        }
        else if (clients_[i].status == WRITE)
        {
          clients_[i].writeFd = responses_[i]->getFileFdForWrite();
          if (clients_[i].writeFd == -1)
          {
            deleteResponses(i);
            responseNot200(i, 500);
          }
          else
          {
            clients_[i].wc.setFd(clients_[i].writeFd);
            clients_[i].wc.setSendData(const_cast<char *>(clients_[i].body.c_str()), clients_[i].body.size());
            clients_[i].responseMessege = responses_[i]->responseMessege;
            deleteResponses(i);
            clients_[i].sc.setSendData(const_cast<char *>(clients_[i].responseMessege.c_str()), clients_[i].responseMessege.size());
          }
          coutLog(i);
        }
        else if (clients_[i].status == READ)
        {
          if (responses_[i]->isCGI == true)
          {
            clients_[i].readFd = responses_[i]->getCgiFd();
          }
          else
          {
            clients_[i].readFd = responses_[i]->getTargetFileFd();
          }
          if (clients_[i].readFd == -1)
          {
            deleteResponses(i);
            responseNot200(i, 500);
          }
          else
            clients_[i].readDataFromFd.setFd(clients_[i].readFd);
        }
        else if (clients_[i].status == SEND)
        {
          clients_[i].responseMessege = responses_[i]->responseMessege;
          coutLog(i);
          deleteResponses(i);
          clients_[i].sc.setSendData(const_cast<char *>(clients_[i].responseMessege.c_str()), clients_[i].responseMessege.size());
        }
        else
          std::cout << "[EMERG] Irregularity status in Response" << std::endl;
      }
      if (clients_[i].writeFd != -1 && FD_ISSET(clients_[i].writeFd, &writeFds_)
        && (clients_[i].status == WRITE || clients_[i].status == READWRITE))
      {
        try
        {
          bool isFinish = clients_[i].wc.SendMessage(SEND_BUFFER_SIZE);
          if (isFinish)
          {
            if (close(clients_[i].writeFd) == -1)
              std::cout << "[emerg] cannot close clients_[" << i << "]writeFd : " << clients_[i].writeFd << std::endl;
            clients_[i].writeFd = -1;
            if (clients_[i].status == WRITE)
              clients_[i].status = SEND;
          }
        }
        catch(const std::exception& e)
        {
          deleteResponses(i);
          clients_[i].initClient();
          std::cerr << e.what() << '\n';
        }
      }
      if (clients_[i].status == READ || clients_[i].status == READWRITE)
      {
        if (clients_[i].readDataFromFd.isCompleteRead())
        {
          if (close(clients_[i].readFd) == -1)
            std::cout << "[EMERG] cannot close clients_[" << i << "]readFd : " << clients_[i].readFd << std::endl;
          clients_[i].readFd = -1;
          if (responses_[i]->isCGI == true)
          {
            responses_[i]->mergeCgiResult(clients_[i].readDataFromFd.getReadData());
          }
          else
            responses_[i]->AppendBodyOnResponseMessage(clients_[i].readDataFromFd.getReadData());
          debugPrintResponseMessege(i);
          clients_[i].readDataFromFd.clearData();
          clients_[i].responseMessege = responses_[i]->responseMessege;
          clients_[i].sc.setSendData(const_cast<char *>(clients_[i].responseMessege.c_str()), clients_[i].responseMessege.size());
          clients_[i].status = SEND;
          clients_[i].responseCode = responses_[i]->ResponseStatus;
          coutLog(i);
          deleteResponses(i);
        }
      }
      if (FD_ISSET(clients_[i].socketFd, &writeFds_) && clients_[i].status == SEND)
      {
        try
        {
          bool isFinish = clients_[i].sc.SendMessage(SEND_BUFFER_SIZE);
          if (isFinish)
          {
            if (isNotKeepConnectionCode(clients_[i].responseCode))
            {
              clients_[i].initClient();
            }
            else if (clients_[i].hmp.headers_["connection"] == "close")
            {
              clients_[i].initClient();
            }
            else
            {
              clients_[i].status = PARSE_STARTLINE;
              clients_[i].hmp.clearData();
              clients_[i].body.clear();
            }
          }
        }
        catch(const std::exception& e)
        {
          clients_[i].initClient();
          std::cerr << e.what() << '\n';
        }
      }
    }
  }
}

Wevserv::~Wevserv()
{
  for (std::vector<Socket>::iterator itrServer = servers_.begin();
    itrServer != servers_.end();
    itrServer++)
  {
    close(itrServer->get_listenfd());
  }
  for (int i = 0; i < MAX_SESSION; i++)
  {
    deleteResponses(i);
    clients_[i].initClient();
  }
}

// ???????????????????????????????????????????????????????????????????????????????????????portAndHostCombination??????????????????true?????????
bool Wevserv::notBeCreatedSocket(int port, std::string host, \
                                  std::vector<portAndHost>& portAndHostCombination)
{
  for (std::vector<portAndHost>::iterator itrPortAndHost = portAndHostCombination.begin();
    itrPortAndHost != portAndHostCombination.end();
    itrPortAndHost++
  )
  {
    if (port == itrPortAndHost->port && host == itrPortAndHost->host)
      return false;
  }
  portAndHost tmp;
  tmp.port = port;
  tmp.host = host;
  portAndHostCombination.push_back(tmp);
  return true;
}

void Wevserv::setupServers()
{
  try
  {
    std::vector<portAndHost> portAndHostCombination;
    for (std::vector<s_ConfigServer>::iterator itr = c_.configGlobal.servers.begin();
      itr != c_.configGlobal.servers.end();
      itr++
    )
    {
      if (notBeCreatedSocket(itr->port, itr->host, portAndHostCombination))
        servers_.push_back(Socket(itr->port, itr->host));
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    exit(1);
  }
}

void Wevserv::fetchAllCGIExtensionsFromConfig()
{
  for(std::vector<std::string>::iterator itr = c_.configGlobal.configCommon.cgiScripts.begin();
      itr != c_.configGlobal.configCommon.cgiScripts.end();
      ++itr)
  {
    cgiScripts_.push_back(*itr);
  }
  for(std::vector<s_ConfigServer>::iterator itrServer = c_.configGlobal.servers.begin();
      itrServer != c_.configGlobal.servers.end();
      ++itrServer)
  {
    for(std::vector<std::string>::iterator itr = itrServer->configCommon.cgiScripts.begin();
        itr != itrServer->configCommon.cgiScripts.end();
        ++itr)
    {
      cgiScripts_.push_back(*itr);
    }
    for(std::vector<s_ConfigLocation>::iterator itrLocation = itrServer->locations.begin();
        itrLocation != itrServer->locations.end();
        ++itrLocation)
    {
      for(std::vector<std::string>::iterator itr = itrLocation->configCommon.cgiScripts.begin();
          itr != itrLocation->configCommon.cgiScripts.end();
          ++itr)
      {
        cgiScripts_.push_back(*itr);
      }
    }
  }
}

void Wevserv::initFD()
{
  FD_ZERO(&readFds_);
  FD_ZERO(&writeFds_);
  for (std::vector<Socket>::iterator itrServer = servers_.begin();
    itrServer != servers_.end();
    itrServer++)
  {
    FD_SET(itrServer->get_listenfd(), &readFds_);
    if (maxFd_ < (itrServer->get_listenfd() + 1))
      maxFd_ = itrServer->get_listenfd() + 1;
  }
  for (int i = 0; i < MAX_SESSION; i++)
  {
    if (clients_[i].socketFd != -1)
    {
      FD_SET(clients_[i].socketFd, &readFds_);
      if (clients_[i].status == SEND && clients_[i].socketFd != -1)
        FD_SET(clients_[i].socketFd, &writeFds_);
      if (maxFd_ < (clients_[i].socketFd + 1))
        maxFd_ = clients_[i].socketFd + 1;
    }
    if (clients_[i].writeFd != -1)
    {
      if ((clients_[i].status == WRITE || clients_[i].status == READWRITE)
        && clients_[i].writeFd != -1)
        FD_SET(clients_[i].writeFd, &writeFds_);
      if (maxFd_ < (clients_[i].writeFd + 1))
        maxFd_ = clients_[i].writeFd + 1;
    }
    if (clients_[i].readFd != -1)
    {
      FD_SET(clients_[i].readFd, &readFds_);
      if (maxFd_ < (clients_[i].readFd + 1))
        maxFd_ = clients_[i].readFd + 1;
    }
    if (c_.getDebugLevel() >= 2)
      std::cout << "[DEBUG]maxFd : " << maxFd_ << std::endl;
  }
}

bool Wevserv::isNotKeepConnectionCode(int code)
{
  switch (code)
  {
  case 400:
  case 408:
  case 409:
  case 413:
  case 500:
  case 501:
  case 502:
  case 503:
  case 504:
  case 505:
    return true;
  }
  return false;
}

void Wevserv::responseNot200(int i, int code)
{
  responses_[i] = new Response(code ,clients_[i], c_);
  if (clients_[i].status == READ)
  {
    clients_[i].readFd = responses_[i]->getTargetFileFd();
    clients_[i].readDataFromFd.setFd(clients_[i].readFd);
    clients_[i].responseCode = code;
    coutLog(i);
  }
  else if (clients_[i].status == SEND)
  {
    clients_[i].responseMessege = responses_[i]->responseMessege;
    deleteResponses(i);
    clients_[i].responseCode = code;
    clients_[i].sc.setSendData(const_cast<char *>(clients_[i].responseMessege.c_str()), clients_[i].responseMessege.size());
    coutLog(i);
  }
  else
  {
    std::cout << "[emerg] Irregularity status in Response" << std::endl;
    deleteResponses(i);
    std::string response = ft_make_dummy_response(400);
    clients_[i].sc.setSendData(const_cast<char *>(response.c_str()), response.size());
    clients_[i].responseCode = 400;
    clients_[i].status = SEND;
  }
}

void Wevserv::coutLog(int i)
{
  std::string log;
  log += clients_[i].ip;
  log += " [";
  log += getTime();
  log += "] ";
  log += ft_itos(clients_[i].responseCode);
  log += " \"";
  log += clients_[i].hmp.getRequestLine();
  log += "\" ";
  if (clients_[i].hmp.headers_["referer"] == "")
    log += "-";
  else
  {
    log += "\"";
    log += clients_[i].hmp.headers_["referer"];
    log += "\"";
  }
  log += " ";
  if (clients_[i].hmp.headers_["user-agent"] == "")
    log += "-";
  else
  {
    log += "\"";
    log += clients_[i].hmp.headers_["user-agent"];
    log += "\"";
  }
  std::cout << log << std::endl;
}

void Wevserv::deleteResponses(int i)
{
  delete responses_[i];
  responses_[i] = NULL;
}

std::map<int, std::string> Wevserv::getMonth()
{
	std::map<int, std::string> month;
	month[0] = "Jan";
	month[1] = "Feb";
	month[2] = "Mar";
	month[3] = "Apr";
	month[4] = "May";
	month[5] = "Jun";
	month[6] = "Jul";
	month[7] = "Aug";
	month[8] = "Sep";
	month[9] = "Oct";
	month[10] = "Nov";
	month[11] = "Dec";
	return (month);
}

std::string Wevserv::ft_ito00(int n)
{
  std::string ret;
  if (n <= 9)
  {
    ret += '0';
    ret += '0' + n;
    return ret;
  }
  while (n > 0)
  {
    char c[2];
    c[0] = '0' + n % 10;
    c[1] = '\0';
    ret.insert(0, std::string(c));
    n /= 10;
  }
  return (ret);
}

std::string Wevserv::getTime()
{
  std::string timestamp;
	time_t timer;
	struct tm *gmt;
	time(&timer);
	gmt = gmtime(&timer);
	timestamp.append(ft_ito00(gmt->tm_mday) + "/");
	timestamp.append(getMonth()[gmt->tm_mon] + "/");
	timestamp.append(ft_ito00(gmt->tm_year + 1900) + " ");
	timestamp.append(ft_ito00(gmt->tm_hour) + ":" + ft_ito00(gmt->tm_min) + ":" + ft_ito00(gmt->tm_sec));
  return timestamp;
}

void Wevserv::debugPrintGetRecvData(int i)
{
  if (c_.getDebugLevel() >= 2)
  {
    std::cout << "--recvData-----------------------------" << std::endl;
    std::cout << clients_[i].receivedData.getRecvData();
    std::cout << "---------------------------------------" << std::endl;
  }
}

void Wevserv::debugPrintGetReadData(int i)
{
  if (c_.getDebugLevel() >= 3)
  {
    std::cout << "--readData-----------------------------" << std::endl;
    std::cout << clients_[i].readDataFromFd.getReadData();
    std::cout << "---------------------------------------" << std::endl;
  }
}

void Wevserv::debugPrintExtractedData(int i)
{
  if (c_.getDebugLevel() >= 2)
  {
    std::cout << "--extractedData_-----------------------" << std::endl;
    std::cout << clients_[i].receivedData.getExtractedData() << std::endl;
    std::cout << "---------------------------------------" << std::endl;
  }
}

void Wevserv::debugPrintStartLine(int i)
{
  if (c_.getDebugLevel() >= 1)
  {
    std::cout << "--startLine----------------------------" << std::endl;
    std::cout << "method = " << clients_[i].hmp.getMethod() << std::endl;
    std::cout << "request-target = " << clients_[i].hmp.getRequestTarget() << std::endl;
    std::cout << "HTTP-version = " << clients_[i].hmp.getHTTPVersion() << std::endl;
    std::cout << "absolute-path = " << clients_[i].hmp.getAbsolutePath() << std::endl;
    std::cout << "query = " << clients_[i].hmp.getQuery() << std::endl;
    std::cout << "---------------------------------------" << std::endl;
  }
}

void Wevserv::debugPrintHeaders(int i)
{
  if (c_.getDebugLevel() >= 1)
  {
    std::map<std::string, std::string> headers = clients_[i].hmp.getHeaders();
    std::cout << "--headers------------------------------" << std::endl;
    for(std::map<std::string, std::string>::const_iterator itr = headers.begin(); itr != headers.end(); ++itr)
      std::cout << "\"" << itr->first << "\" = \"" << itr->second << "\"\n";
    std::cout << "---------------------------------------" << std::endl;
  }
}

void Wevserv::debugPrintResponceData(int i)
{
  if (c_.getDebugLevel() >= 1)
  {
    std::cout << "--responceData-------------------------" << std::endl;
    std::cout << "response_code  : " << responses_[i]->ResponseStatus << std::endl;
    std::cout << "file_path      : " << responses_[i]->targetFilePath << std::endl;
    std::cout << "file_length    : " << responses_[i]->getContentLength() << std::endl;
    std::cout << "open_fd        : " << responses_[i]->getTargetFileFd() << std::endl;
    std::cout << "client_status  : " << clients_[i].status << std::endl;
    std::cout << "responseMessege  " << std::endl << responses_[i]->responseMessege << std::endl;
    std::cout << "---------------------------------------" << std::endl;
  }
}

void Wevserv::debugPrintRequestBody(int i)
{
  if (c_.getDebugLevel() >= 2)
  {
    std::cout << "--body---------------------------------" << std::endl;
    std::cout << clients_[i].body << std::endl;
    std::cout << "---------------------------------------" << std::endl;
  }
}

void Wevserv::debugPrintResponseMessege(int i)
{
  if (c_.getDebugLevel() >= 2)
  {
    std::cout << "--responseMessege----------------------" << std::endl;
    std::cout << responses_[i]->responseMessege << std::endl;
    std::cout << "---------------------------------------" << std::endl;
  }
}