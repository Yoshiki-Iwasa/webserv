#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <vector>
#include <string>
#include <iostream>
#include "recvData.hpp"
#include "readData.hpp"
#include "HTTPMessageParser.hpp"
#include "getChunked.hpp"
#include "sendController.hpp"

enum clientStatus {PARSE_STARTLINE, PARSE_HEADER, RESV_BODY, CREATE_RESPONSE, READ, WRITE, SEND, PARSE_HEADER_AFTER_CHUNKD, READWRITE, NUM_OF_CLIENTSTATUS};

class Client
{
 public:
  // fd
  int socketFd;
  int readFd;
  int writeFd;
  int pipeReadFd;
  int pipeWriteFd;

  // どのサーバーに接続したかを識別する情報
  int port;
  std::string host;

  // クライアントの情報
  std::string ip;

  // 各種処理をするためのclass
  recvData receivedData;
  readData readDataFromFd;
  HTTPMessageParser hmp;
  getChunked gc;
  SendController wc;
  SendController sc;

  // 処理状態とフラグ
  enum clientStatus status;
  bool bCGI;
  bool bChunked;
  int responseCode;
  size_t responseFileSize;
  std::string responseMessege;

  // メッセージボディ
  std::string body;
  
  // クライアントからの接続タイムアウト用
  struct timeval lastTvForClient;

  // CGIの実行タイムアウト用
  struct timeval lastTvForCGI;

  // ヘッダの内容を見てボディを受信するかを返す
  // ヘッダに「Transfer-Encoding: chunked」があった場合、bChunkedをtrueに変更する
  bool isNeedBody(std::map<std::string, std::string> headers);

  void initClient();

  Client();
  ~Client();
  bool operator==(const Client&);
  bool operator!=(const Client&);

 private:
  Client(const Client&);
  Client& operator=(const Client&);

  //テスト用
  static int dummyFd;
};

#endif