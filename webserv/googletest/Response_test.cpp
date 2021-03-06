#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Client.hpp"
#include "../Config.hpp"
#include "../Response.hpp"
#include "../parseConfig.hpp"

// Google TestでのMatcherの活用
// https://goyoki.hatenablog.com/entry/2013/01/16/003803
using ::testing::MatchesRegex;
using ::testing::Ge;

// googletestのインストール手順
// https://rinatz.github.io/cpp-book/test-how-to-gtest/
// g++ -std=c++11 ../HTTPMessageParser.cpp HTTPMessageParser_test.cpp -o test -L/usr/local/lib -pthread -lgtest -lgtest_main

TEST(Response_test, webserv_01)
{
  {
    const char* configfile = "testcase/webserv.conf";
    Config config_;
    parseConfig(configfile, config_);

    // 0001
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      size_t TargetSize = Response.getContentLength();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    }
    // 0002
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    }
    // 0003
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/aaa/index.html";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0aaa/index.html", Response.targetFilePath);
    }
    // 0004
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/aaa/";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0aaa/default.html", Response.targetFilePath);
    }
    // 0005
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/aa/index.html";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0aa/index.html", Response.targetFilePath);
    }
    // 0006
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/aa/";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0aa/index.html", Response.targetFilePath);
    }
    // 0140
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/aa";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0aa/index.html", Response.targetFilePath);
    }
    // 0141
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/zz";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
    }
    // 0007
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/www/aaa/index.html";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0/404.html", Response.targetFilePath);
    }
  }
}

TEST(Response_test, webserv_02)
{
  const char* configfile = "testcase/webserv.conf";
  Config config_;
  parseConfig(configfile, config_);  
  {
    // 0008
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/bbb/index.html";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/1bbb/index.html", Response.targetFilePath);
    }
    // 0009
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/bb/index.html";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/1bb/index.html", Response.targetFilePath);
    }
    // 0010
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/www/bb/index.html";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
      EXPECT_EQ("", Response.targetFilePath);
    }
    // 0011
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/1.jpg";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0/1.jpg", Response.targetFilePath);
    }
  }
}

TEST(Response_test, webserv_serverNames)
{
  // 012_webserv_serverNames.conf
  {
    const char* configfile = "testcase/012_webserv_serverNames.conf";
    Config config_;
    parseConfig(configfile, config_);
    // 0012
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/serverNames/5000/default/index.html", Response.targetFilePath);
    }
    // 0013
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "server10";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/serverNames/5000/server1x/index.html", Response.targetFilePath);
    }
    // 00183
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "server10:8080";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/serverNames/5000/server1x/index.html", Response.targetFilePath);
    }
    // 0014
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "server11";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/serverNames/5000/server1x/index.html", Response.targetFilePath);
    }
    // 00182
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "server11:5000";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/serverNames/5000/server1x/index.html", Response.targetFilePath);
    }    
    // 0015
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "server20";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/serverNames/5001/server2x/index.html", Response.targetFilePath);
    }
    // 00184
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "server20:5001";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/serverNames/5001/server2x/index.html", Response.targetFilePath);
    }
    // 0016
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "server";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/serverNames/5001/server1x/index.html", Response.targetFilePath);
    }

    // 0017
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["host"] = "127.0.0.1:5000";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/serverNames/5000/default/index.html", Response.targetFilePath);
    }
  }  
}

TEST(Response_test, webserv_error)
{
  const char* configfile = "testcase/webserv.conf";
  Config config_;
  parseConfig(configfile, config_);  
  {
    // 0018
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/none";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0/404.html", Response.targetFilePath);
    }
    // 0019
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/aaa/none";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0/404.html", Response.targetFilePath);
    }
    // 0020
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/aa/none";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0/404.html", Response.targetFilePath);
    }
    // 0021
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/root.html";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int TargetFileFd = Response.getTargetFileFd();
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(403, ResponseStatus);
    }
    // 0022
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/none";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(403, ResponseStatus);
      EXPECT_EQ("", Response.targetFilePath);
    }
    // 0023
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.absolutePath_ = "/bbb/none";
      client_.hmp.headers_["host"] = "127.0.0.1";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(403, ResponseStatus);
      EXPECT_EQ("", Response.targetFilePath);
    }
  }
}

TEST(Response_test, webserv_index)
{
  const char* configfile = "testcase/015_index.conf";
  Config config_;
  parseConfig(configfile, config_);  
  {
    // 0024
    try
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0024" << '\n';
      std::cerr << e.what() << '\n';
    }
    
    // 0025
    try
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/aaap1/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0aaa/default.html", Response.targetFilePath);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0025" << '\n';
      std::cerr << e.what() << '\n';
    }
    // 0026
    try
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/aaap2/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0aaa/index.html", Response.targetFilePath);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0026" << '\n';
      std::cerr << e.what() << '\n';
    }
    // 0027
    try
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/aaap3/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0aaa/default.html", Response.targetFilePath);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0027" << '\n';
      std::cerr << e.what() << '\n';
    }
    // 0028
    try
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/aaap4/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0aaa/default.html", Response.targetFilePath);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0028" << '\n';
      std::cerr << e.what() << '\n';
    }
    // 0029
    try
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/aaap5/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0029" << '\n';
      std::cerr << e.what() << '\n';
    }
    // 0030
    try
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/aa/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0030" << '\n';
      std::cerr << e.what() << '\n';
    }
    // 0031
    try
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/1//index.html", Response.targetFilePath);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0031" << '\n';
      std::cerr << e.what() << '\n';
    }
    // 0032
    try
    {
      Client client_;
      client_.port = 5001;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/bbb/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0032" << '\n';
      std::cerr << e.what() << '\n';
    }
    // 00
    {
      // Client client_;
      // client_.port = ;
      // client_.host = "*";
      // client_.hmp.method_ = httpMessageParser::GET;
      // client_.hmp.headers_["host"] = "";
      // client_.hmp.absolutePath_ = "";

      // Response Response(client_, config_);
      // int ResponseStatus = Response.ResponseStatus;

      // EXPECT_EQ(, ResponseStatus);
      // EXPECT_EQ("", Response.targetFilePath);
      // EXPECT_EQ("", Response.errorFilePath);
    }
  }
}

TEST(Response_test, webserv_index_2)
{
  const char* configfile = "testcase/015_index2.conf";
  Config config_;
  parseConfig(configfile, config_);  
  {
    // 0056
    try
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(403, ResponseStatus);
    }
    catch(const std::exception& e)
    {
      std::cerr << "0024" << '\n';
      std::cerr << e.what() << '\n';
    }
  }
}

TEST(Response_test, allow)
{
  const char* configfile = "testcase/016_allow.conf";
  Config config_;
  parseConfig(configfile, config_);  
  {
    // 0033
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    }
    // // 0034
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::HEAD;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(200, ResponseStatus);
    //   EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    // }
    // // 0035
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::POST;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(200, ResponseStatus);
    //   EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    // }
    // // 0036
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::PUT;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(200, ResponseStatus);
    //   EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    // }
    // // 0037
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::DELETE;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(200, ResponseStatus);
    //   EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    // }
    // // 0038
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::CONNECT;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(200, ResponseStatus);
    //   EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    // }
    // // 0039
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::OPTIONS;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(200, ResponseStatus);
    //   EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    // }
    // // 0040
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::TRACE;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(200, ResponseStatus);
    //   EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    // }
    // 0041
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/get/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/0/index.html", Response.targetFilePath);
    }
    // // 0042
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::POST;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/get/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(405, ResponseStatus);
    //   std::string &ResponseMessage = Response.responseMessege;
    //   EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: GET\r\n.*"));
    // }
    // // 0042
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::POST;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/get/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(405, ResponseStatus);
    //   std::string &ResponseMessage = Response.responseMessege;
    //   EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: GET\r\n.*"));
    // }
    // // 0043
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::HEAD;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/get/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(405, ResponseStatus);
    //   std::string &ResponseMessage = Response.responseMessege;
    //   EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: GET\r\n.*"));
    // }
    // // 0044
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::PUT;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/get/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(405, ResponseStatus);
    //   std::string &ResponseMessage = Response.responseMessege;
    //   EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: GET\r\n.*"));
    // }
    // // 0045
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::DELETE;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/get/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(405, ResponseStatus);
    //   std::string &ResponseMessage = Response.responseMessege;
    //   EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: GET\r\n.*"));
    // }
    // // 0046
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::CONNECT;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/get/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(405, ResponseStatus);
    //   std::string &ResponseMessage = Response.responseMessege;
    //   EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: GET\r\n.*"));
    // }
    // // 0047
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::OPTIONS;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/get/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(405, ResponseStatus);
    //   std::string &ResponseMessage = Response.responseMessege;
    //   EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: GET\r\n.*"));
    // }
    // // 0048
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::TRACE;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/get/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(405, ResponseStatus);
    //   std::string &ResponseMessage = Response.responseMessege;
    //   EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: GET\r\n.*"));
    // }
    // 0049
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/head/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(405, ResponseStatus);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: HEAD\r\n.*"));
    }
    // 0050
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/put/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(405, ResponseStatus);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: PUT\r\n.*"));
    }
    // 0051
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/delete/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(405, ResponseStatus);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: DELETE\r\n.*"));
    }
    // 0052
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/connect/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(405, ResponseStatus);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: CONNECT\r\n.*"));
    }
    // 0053
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/options/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(405, ResponseStatus);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: OPTIONS\r\n.*"));
    }
    // 0054
    {
      Client client_;
      client_.port = 5000;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/trace/";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(405, ResponseStatus);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: TRACE\r\n.*"));
    }
    // // 0055
    // {
    //   Client client_;
    //   client_.port = 5000;
    //   client_.host = "*";
    //   client_.hmp.method_ = httpMessageParser::PUT;
    //   client_.hmp.headers_["host"] = "127.0.0.1";
    //   client_.hmp.absolutePath_ = "/getheadpost/";

    //   Response Response(client_, config_);
    //   int ResponseStatus = Response.ResponseStatus;

    //   EXPECT_EQ(405, ResponseStatus);
    //   std::string &ResponseMessage = Response.responseMessege;
    //   EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nAllow: POST,HEAD,GET\r\n.*"));
    // }
  }
}

TEST(Response_test, AcceptLanguage)
{
  const char* configfile = "testcase/017_acceptlanguage.conf";
  Config config_;
  parseConfig(configfile, config_);  
  {
    // 0057
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "en;q=0.8, ja;q=0.9, *";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html", Response.targetFilePath);
    }
  }
  {
    // 0058
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/index.html";
      client_.hmp.headers_["accept-language"] = "ja";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nContent-Language: ja\r\n.*"));
    }
  }
  {
    // 0059
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nContent-Language: ja\r\n.*"));
    }
  }
  {
    // 0060
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "*";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html", Response.targetFilePath);
    }
  }
  {
    // 0061
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "en";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.en", Response.targetFilePath);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nContent-Language: en\r\n.*"));
    }
  }
  {
    // 0062
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja, en;q=0.9";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nContent-Language: ja\r\n.*"));
    }
  }
  {
    // 0063
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "en;q=0.9";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.en", Response.targetFilePath);
      std::string &ResponseMessage = Response.responseMessege;
      EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nContent-Language: en\r\n.*"));
    }
  }
  {
    // 0064
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "fr";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html", Response.targetFilePath);
    }
  }
  {
    // 0065
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "en;q=0.9, ja";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0066
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "fr, ja";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0067
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "fr, *";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html", Response.targetFilePath);
    }
  }
  {
    // 0068
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "fr, ja, en";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0069
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=1.000";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0070
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=1.00";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0071
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=1.0";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0072
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=1.";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0073
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=1";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0074
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=1.0000";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(406, ResponseStatus);
    }
  }
  {
    // 0075
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=1.2";
      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(406, ResponseStatus);
    }
  }
  {
    // 0076
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=2";
      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(406, ResponseStatus);
    }
  }
  {
    // 0077
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja,";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0078
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=0.999";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0079
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=0.99";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0080
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=0.9";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0081
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=0.";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0082
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=0";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0083
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "zz";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html", Response.targetFilePath);
    }
  }
  {
    // 0084
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=2, en";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(406, ResponseStatus);
    }
  }
  {
    // 0085
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=2, en,";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(406, ResponseStatus);
    }
  }
  {
    // 0086
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=2, en;,";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(406, ResponseStatus);
    }
  }
  {
    // 0087
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=0.11, en;q=0.11, *;q=0.11";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0088
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "ja;q=0.111, en;q=0.11, *;q=0.1";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html.ja", Response.targetFilePath);
    }
  }
  {
    // 0089
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/";
      client_.hmp.headers_["accept-language"] = "fr,de;q=0.5,el;q=0.3";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(200, ResponseStatus);
      EXPECT_EQ("/tmp/webserv/acceptlanguage/index.html", Response.targetFilePath);
    }
  }
  {
    // 0182
    {
      Client client_;
      client_.port = 8080;
      client_.host = "*";
      client_.hmp.method_ = httpMessageParser::GET;
      client_.hmp.headers_["host"] = "127.0.0.1";
      client_.hmp.absolutePath_ = "/none.html";
      client_.hmp.headers_["accept-language"] = "ja,en-US;q=0.9,en;q=0.8";

      Response Response(client_, config_);
      int ResponseStatus = Response.ResponseStatus;

      EXPECT_EQ(404, ResponseStatus);
    }
  }
}

TEST(Response_test, Authorization)
{
  const char* configfile = "testcase/018_basicauth.conf";
  Config config_;
  parseConfig(configfile, config_);
  {
    // 0090
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["authorization"] = "Basic dXNlcjpwYXNzd29yZA==";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html", Response.targetFilePath);
  }
  {
    // 0091
    Client client_;
    client_.port = 8081;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    // user:password
    client_.hmp.headers_["authorization"] = "Basic dXNlcjpwYXNzd29yZA==";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html", Response.targetFilePath);
  }
  {
    // 0092
    Client client_;
    client_.port = 8082;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    // ユーザー:パスワード
    client_.hmp.headers_["authorization"] = "Basic 44Om44O844K244O8OuODkeOCueODr+ODvOODiQ==";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html", Response.targetFilePath);
  }
  {
    // 0093
    Client client_;
    client_.port = 8081;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    // user:none
    client_.hmp.headers_["authorization"] = "Basic dXNlcjpub25l";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(401, ResponseStatus);
  }
  {
    // 0094
    Client client_;
    client_.port = 8081;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(401, ResponseStatus);
  }
}

TEST(Response_test, AcceptLanguageAndAcceptCharset)
{
  const char* configfile = "testcase/020_acceptcharaset.conf";
  Config config_;
  parseConfig(configfile, config_);  
  // 0095
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-language"] = "en";
    client_.hmp.headers_["accept-charset"] = "iso-8859-15;q=0.9, utf-8, *;q=0.5";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8.en", Response.targetFilePath);
  }
  // 0096
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "iso-8859-15;q=0.8, utf-8;q=0.9, *";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html", Response.targetFilePath);
  }
  // 0097
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8, iso-8859-15;q=0.9, *;q=0.5";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0098
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0099
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "*";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html", Response.targetFilePath);
  }
  // 0100
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "iso-8859-15";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.iso-8859-15", Response.targetFilePath);
  }
  // 0101
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8, iso-8859-15;q=0.9";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0102
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "iso-8859-15;q=0.9";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.iso-8859-15", Response.targetFilePath);
  }
  // 0103
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "EUC_JP";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html", Response.targetFilePath);
  }
  // 0104
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "iso-8859-15;q=0.9, utf-8";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0105
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "EUC_JP, utf-8";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0106
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "EUC_JP, *";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html", Response.targetFilePath);
  }
  // 0107
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "EUC_JP, utf-8, iso-8859-15";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0108
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=1.000";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0109
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=1.00";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0110
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=1.0";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0111
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=1.";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0112
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0113
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=1.0000";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(406, ResponseStatus);
  }
  // 0114
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=1.2";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(406, ResponseStatus);
  }
  // 0115
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=2";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(406, ResponseStatus);
  }
  // 0116
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8,";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0117
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=0.999";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0118
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=0.99";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0119
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=0.9";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0120
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=0.";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0121
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=0";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }
  // 0122
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "zz";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html", Response.targetFilePath);
  }
  // 0123
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=2, iso-8859-15";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(406, ResponseStatus);
  }
  // 0124
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=2, iso-8859-15,";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(406, ResponseStatus);
  }
  // 0125
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=2, iso-8859-15;,";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(406, ResponseStatus);
  }
  // 0126
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=0.11, iso-8859-15;q=0.11, *;q=0.11";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }  
  // 0127
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "utf-8;q=0.111, iso-8859-15;q=0.11, *;q=0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html.utf-8", Response.targetFilePath);
  }

  // 0128
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["accept-charset"] = "EUC_JP,de;q=0.5,el;q=0.3";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/base/index.html", Response.targetFilePath);
  }
}

TEST(Response_test, PUT)
{
  const char* configfile = "testcase/021_put.conf";
  Config config_;
  parseConfig(configfile, config_);

  // 0129
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["content-length"] = "10";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(204, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/put/index.html", Response.targetFilePath);
  }
  // 0130
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(204, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/put/index.html", Response.targetFilePath);
  }
  // 0131
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/index.htm";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(201, ResponseStatus);
    // EXPECT_EQ(204, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/put/index.htm", Response.targetFilePath);
  }
  // 0132
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/root.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(403, ResponseStatus);
  }
  // 0133
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/root/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(403, ResponseStatus);
  }
  // 0134
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/001/index.htm";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(204, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/put/001/index.htm", Response.targetFilePath);
  }
  // 0135
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/www/index.htm";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(204, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/put/alias/index.htm", Response.targetFilePath);
  }
  // 0136
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/auth/index.htm";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(401, ResponseStatus);
  }
  // 0137
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/auth/index.htm";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";
    client_.hmp.headers_["authorization"] = "Basic dXNlcjpwYXNzd29yZA==";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(204, ResponseStatus);
    EXPECT_EQ("/tmp/webserv/put/auth/index.htm", Response.targetFilePath);
  }  
  // 0138
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(403, ResponseStatus);
  }
  // 0139
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/none/index.htm";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(201, ResponseStatus);
  }
  // 0140
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/limit/putdata.txt";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";
    client_.body = "01234567890";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(413, ResponseStatus);
  }
  // 0141
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/limit/putdata.txt";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["content-length"] = "11";
    client_.body = "01234567890";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(413, ResponseStatus);
  }  
}

TEST(Response_test, CGI)
{
  const char* configfile = "testcase/022_cgiscripts.conf";
  Config config_;
  parseConfig(configfile, config_);
  ssize_t read_size;
  char buf[1000];

  // 0142
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/index.php";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.query_ = "name=ap2";
    client_.hmp.requestTarget_ = "/index.php?name=ap2";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_LE(3, Response.getCgiFd());

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    // std::cout << "CGIの出力" << std::endl << cgiOutput << std::endl;
    // std::cout << "Response.getCgiFd() = " << Response.getCgiFd() << std::endl;
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[GATEWAY_INTERFACE] => CGI/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[QUERY_STRING] => name=ap2\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REMOTE_ADDR] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_METHOD] => GET\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_URI] => /index.php\\?name=ap2\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_NAME] => /index.php\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_FILENAME] => /tmp/webserv/base/index.php\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_NAME] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PORT] => 8080\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PROTOCOL] => HTTP/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_SOFTWARE] => webserv\n.*"));
    close(Response.getCgiFd());
  }
  // 0143
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/index.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.query_ = "name=ap2";
    client_.hmp.requestTarget_ = "/index.cgi?name=ap2";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_LE(3, Response.getCgiFd());

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    // std::cout << "CGIの出力" << std::endl << buf << std::endl;
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[GATEWAY_INTERFACE] => CGI/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[QUERY_STRING] => name=ap2\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REMOTE_ADDR] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_METHOD] => GET\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_URI] => /index.cgi\\?name=ap2\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_NAME] => /index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_FILENAME] => /tmp/webserv/base/index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_NAME] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PORT] => 8080\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PROTOCOL] => HTTP/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_SOFTWARE] => webserv\n.*"));
    close(Response.getCgiFd());
  }
  // 0144
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/index.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.query_ = "name+ap2";
    client_.hmp.requestTarget_ = "/index.cgi?name+ap2";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_LE(3, Response.getCgiFd());

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    // std::cout << "CGIの出力" << std::endl << buf << std::endl;
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[GATEWAY_INTERFACE] => CGI/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[QUERY_STRING] => name\\+ap2\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REMOTE_ADDR] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_METHOD] => GET\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_URI] => /index.cgi\\?name\\+ap2\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_NAME] => /index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_FILENAME] => /tmp/webserv/base/index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_NAME] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PORT] => 8080\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PROTOCOL] => HTTP/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_SOFTWARE] => webserv\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[ARGV\\[0]] => name\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[ARGV\\[1]] => ap2\n.*"));
    close(Response.getCgiFd());
  }
  // 0145
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/index.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.query_ = "param=name+ap2";
    client_.hmp.requestTarget_ = "/index.cgi?param=name+ap2";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_LE(3, Response.getCgiFd());

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    // std::cout << "CGIの出力" << std::endl << buf << std::endl;
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[GATEWAY_INTERFACE] => CGI/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[QUERY_STRING] => param=name\\+ap2\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REMOTE_ADDR] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_METHOD] => GET\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_URI] => /index.cgi\\?param=name\\+ap2\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_NAME] => /index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_FILENAME] => /tmp/webserv/base/index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_NAME] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PORT] => 8080\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PROTOCOL] => HTTP/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_SOFTWARE] => webserv\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[ARGV\\[0]] => \n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[ARGV\\[1]] => \n.*"));
    close(Response.getCgiFd());
  }
  // 0146
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/index.php";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.query_ = "";
    client_.hmp.requestTarget_ = "/index.php/001/002";
    client_.hmp.pathinfo_ = "001/002";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_LE(3, Response.getCgiFd());

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    // std::cout << "CGIの出力" << std::endl << cgiOutput << std::endl;
    // std::cout << "Response.getCgiFd() = " << Response.getCgiFd() << std::endl;
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[GATEWAY_INTERFACE] => CGI/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[PATH_INFO] => /001/002\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[PATH_TRANSLATED] => /tmp/webserv/base/001/002\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[QUERY_STRING] => \n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REMOTE_ADDR] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_METHOD] => GET\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_URI] => /index.php/001/002\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_NAME] => /index.php\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_FILENAME] => /tmp/webserv/base/index.php\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_NAME] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PORT] => 8080\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PROTOCOL] => HTTP/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_SOFTWARE] => webserv\n.*"));
    close(Response.getCgiFd());
  }  
  // 0147
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/index.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.query_ = "";
    client_.hmp.requestTarget_ = "/index.cgi/001/002";
    client_.hmp.pathinfo_ = "001/002";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_LE(3, Response.getCgiFd());

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    // std::cout << "CGIの出力" << std::endl << buf << std::endl;
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[GATEWAY_INTERFACE] => CGI/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[PATH_INFO] => /001/002\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[PATH_TRANSLATED] => /tmp/webserv/base/001/002\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[QUERY_STRING] => \n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REMOTE_ADDR] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_METHOD] => GET\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_URI] => /index.cgi/001/002\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_NAME] => /index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_FILENAME] => /tmp/webserv/base/index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_NAME] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PORT] => 8080\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PROTOCOL] => HTTP/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_SOFTWARE] => webserv\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[ARGV\\[0]] => \n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[ARGV\\[1]] => \n.*"));
    close(Response.getCgiFd());
  }
}

TEST(Response_test, HEAD)
{
  const char* configfile = "testcase/022_cgiscripts.conf";
  Config config_;
  parseConfig(configfile, config_);

  // 0148
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::HEAD;
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
  }
  // 0149
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::HEAD;
    client_.hmp.absolutePath_ = "/0";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
  }
  // 0149
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::HEAD;
    client_.hmp.absolutePath_ = "/1";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(404, ResponseStatus);
  }
  // 0150
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::HEAD;
    client_.hmp.absolutePath_ = "/index.php";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
  }
  // 0151
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::HEAD;
    client_.hmp.absolutePath_ = "/index.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
  }
  // 0152
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::HEAD;
    client_.hmp.absolutePath_ = "/1.jpg";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
  }  
}

TEST(Response_test, POST)
{
  const char* configfile = "testcase/023_postfile.conf";
  Config config_;
  parseConfig(configfile, config_);

  // 0153
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["content-length"] = "10";
    client_.body = "0123456789";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(201, ResponseStatus);
    EXPECT_LE(3, Response.getFileFdForWrite());
  }
  // 0154
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";
    client_.body = "0123456789";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(201, ResponseStatus);
    EXPECT_LE(3, Response.getFileFdForWrite());
  }
  // 0155
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/root/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";
    client_.body = "0123456789";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(201, ResponseStatus);
    EXPECT_LE(3, Response.getFileFdForWrite());
  }
  // 0156
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/www/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(201, ResponseStatus);
    EXPECT_LE(3, Response.getFileFdForWrite());
  }
  // 0157
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/none/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(403, ResponseStatus);
  }
  // 0158
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/limit/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["transfer-encoding"] = "chunked";
    client_.body = "01234567890";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(413, ResponseStatus);
  }
  // 0159
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/limit/";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["content-length"] = "11";
    client_.body = "01234567890";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(413, ResponseStatus);
  }
}

TEST(Response_test, methodDELETE)
{
  const char* configfile = "testcase/170_delete.conf";
  Config config_;
  parseConfig(configfile, config_);

  // 0159
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["content-length"] = "10";

    Response Response_put(client_, config_);
    int ResponseStatus = Response_put.ResponseStatus;

    client_.hmp.method_ = httpMessageParser::DELETE;
    client_.hmp.absolutePath_ = "/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    Response Response(client_, config_);
    ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(204, ResponseStatus);
  }
  // 0166
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/alias/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["content-length"] = "10";

    Response Response_put(client_, config_);
    int ResponseStatus = Response_put.ResponseStatus;

    client_.hmp.method_ = httpMessageParser::DELETE;
    client_.hmp.absolutePath_ = "/alias/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    Response Response(client_, config_);
    ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(204, ResponseStatus);
  }  
  // 0160
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::DELETE;
    client_.hmp.absolutePath_ = "/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(404, ResponseStatus);
  }
  // 0161
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/www/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["content-length"] = "10";

    Response Response_put(client_, config_);
    int ResponseStatus = Response_put.ResponseStatus;

    client_.hmp.method_ = httpMessageParser::DELETE;
    client_.hmp.absolutePath_ = "/www/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    Response Response(client_, config_);
    ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(204, ResponseStatus);
  }
  // 0162
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::PUT;
    client_.hmp.absolutePath_ = "/www/dir/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.hmp.headers_["content-length"] = "10";

    Response Response_put(client_, config_);
    int ResponseStatus = Response_put.ResponseStatus;

    client_.hmp.method_ = httpMessageParser::DELETE;
    client_.hmp.absolutePath_ = "/www/dir/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    Response Response(client_, config_);
    ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(204, ResponseStatus);
  }
  // 0163
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::DELETE;
    client_.hmp.absolutePath_ = "/none/index.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(403, ResponseStatus);
  }
  // 0164
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::DELETE;
    client_.hmp.absolutePath_ = "/root.html";
    client_.hmp.headers_["host"] = "127.0.0.1";
    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(403, ResponseStatus);
  }
  // 0165
  {
    Client client_put_;
    client_put_.port = 8080;
    client_put_.host = "*";
    client_put_.hmp.method_ = httpMessageParser::PUT;
    client_put_.hmp.absolutePath_ = "/auth/index.htm";
    client_put_.hmp.headers_["host"] = "127.0.0.1";
    client_put_.hmp.headers_["transfer-encoding"] = "chunked";
    client_put_.hmp.headers_["authorization"] = "Basic dXNlcjpwYXNzd29yZA==";

    Response Response_put(client_put_, config_);
    int ResponseStatus = Response_put.ResponseStatus;

    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::DELETE;
    client_.hmp.absolutePath_ = "/auth/index.htm";
    client_.hmp.headers_["host"] = "127.0.0.1";
    Response Response_no_auth(client_, config_);
    ResponseStatus = Response_no_auth.ResponseStatus;
    EXPECT_EQ(401, ResponseStatus);

    client_.hmp.headers_["authorization"] = "Basic dXNlcjpwYXNzd29yZA==";
    Response Response_auth(client_, config_);
    ResponseStatus = Response_auth.ResponseStatus;
    EXPECT_EQ(204, ResponseStatus);
  }
}

TEST(Response_test, Redirect)
{
  const char* configfile = "testcase/180_redirect.conf";
  Config config_;
  parseConfig(configfile, config_);
  {
    // 0166
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
  }
  {
    // 0167
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/playstations4/";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(301, ResponseStatus);
    std::string &ResponseMessage = Response.responseMessege;
    EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nLocation: /ps4/\r\n.*"));    
  }
  {
    // 0168
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/nintendoswith/";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(301, ResponseStatus);
    std::string &ResponseMessage = Response.responseMessege;
    EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nLocation: /ns/\r\n.*"));    
  }
  {
    // 0169
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/sega/megadrive/";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(301, ResponseStatus);
    std::string &ResponseMessage = Response.responseMessege;
    EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nLocation: /sega/md/\r\n.*"));    
  }
  {
    // 0170
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/megadrive/";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
  }
  {
    // 0171
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/playstations4/nintendoswith/";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(301, ResponseStatus);
    std::string &ResponseMessage = Response.responseMessege;
    EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nLocation: /ps4/ns/\r\n.*"));    
  }
  {
    // 0172
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::GET;
    client_.hmp.absolutePath_ = "/sega/playstations4/";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(404, ResponseStatus);
  }
  {
    // 0173
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/playstations4/";
    client_.hmp.headers_["host"] = "127.0.0.1";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(308, ResponseStatus);
    std::string &ResponseMessage = Response.responseMessege;
    EXPECT_THAT(ResponseMessage, MatchesRegex(".*\r\nLocation: /ps4/\r\n.*"));    
  }
}
TEST(Response_test, POST_CGI)
{
  const char* configfile = "testcase/022_cgiscripts.conf";
  Config config_;
  parseConfig(configfile, config_);
  ssize_t read_size;
  char buf[1000];

  // 0174
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/index.php";
    client_.hmp.requestTarget_ = "/index.php";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";
    client_.body = "name=ap2";
    client_.hmp.headers_["content-length"] = "8";
    client_.hmp.headers_["content-type"] = "application/x-www-form-urlencoded";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_LE(3, Response.getCgiFd());
    EXPECT_LE(3, Response.getCgiFdForWrite());

    const char *body = "name=ap2";
    size_t write_size = write(Response.getCgiFdForWrite(), body, 8);

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    // std::cout << "CGIの出力" << std::endl << cgiOutput << std::endl;
    // std::cout << "Response.getCgiFd() = " << Response.getCgiFd() << std::endl;
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[GATEWAY_INTERFACE] => CGI/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REMOTE_ADDR] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_METHOD] => POST\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_URI] => /index.php\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_NAME] => /index.php\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_FILENAME] => /tmp/webserv/base/index.php\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_NAME] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PORT] => 8080\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PROTOCOL] => HTTP/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_SOFTWARE] => webserv\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[name] => ap2\n.*"));
    close(Response.getCgiFd());
  }
  // 0175
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/index.cgi";
    client_.hmp.requestTarget_ = "/index.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";
    client_.body = "name=ap2";
    client_.hmp.headers_["content-length"] = "8";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_LE(3, Response.getCgiFd());
    EXPECT_LE(3, Response.getCgiFdForWrite());

    const char *body = "name=ap2";
    size_t write_size = write(Response.getCgiFdForWrite(), body, 8);   

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    // std::cout << "CGIの出力" << std::endl << cgiOutput << std::endl;
    // std::cout << "Response.getCgiFd() = " << Response.getCgiFd() << std::endl;
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[GATEWAY_INTERFACE] => CGI/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REMOTE_ADDR] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_METHOD] => POST\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[REQUEST_URI] => /index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_NAME] => /index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SCRIPT_FILENAME] => /tmp/webserv/base/index.cgi\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_NAME] => 127.0.0.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PORT] => 8080\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_PROTOCOL] => HTTP/1.1\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[SERVER_SOFTWARE] => webserv\n.*"));
    EXPECT_THAT(cgiOutput, MatchesRegex(".*\\[POST_DATA] => name=ap2\n.*"));
    close(Response.getCgiFd());
  }
  // 0176
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/404.cgi";
    client_.hmp.requestTarget_ = "/404.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";
    client_.body = "name=ap2";
    client_.hmp.headers_["content-length"] = "8";

    Response Response(client_, config_);
    int ResponseStatus = Response.ResponseStatus;

    EXPECT_EQ(200, ResponseStatus);
    EXPECT_LE(3, Response.getCgiFd());
    EXPECT_LE(3, Response.getCgiFdForWrite());

    const char *body = "name=ap2";
    size_t write_size = write(Response.getCgiFdForWrite(), body, 8);   

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    Response.mergeCgiResult(cgiOutput);
    EXPECT_THAT(Response.responseMessege, MatchesRegex("HTTP/1.1 404 Not Found\r\n.*"));
    close(Response.getCgiFd());
  }
  // 0177
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/nocolon.cgi";
    client_.hmp.requestTarget_ = "/nocolon.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";
    client_.body = "name=ap2";
    client_.hmp.headers_["content-length"] = "8";

    Response Response(client_, config_);
    EXPECT_LE(3, Response.getCgiFd());
    EXPECT_LE(3, Response.getCgiFdForWrite());

    const char *body = "name=ap2";
    size_t write_size = write(Response.getCgiFdForWrite(), body, 8);   

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    Response.mergeCgiResult(cgiOutput);
    int ResponseStatus = Response.ResponseStatus;
    EXPECT_EQ(500, ResponseStatus);
    close(Response.getCgiFd());
  }
  // 0178
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/bad_cgi_001.cgi";
    client_.hmp.requestTarget_ = "/bad_cgi_001.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";
    client_.body = "name=ap2";
    client_.hmp.headers_["content-length"] = "8";

    Response Response(client_, config_);
    EXPECT_LE(3, Response.getCgiFd());
    EXPECT_LE(3, Response.getCgiFdForWrite());

    const char *body = "name=ap2";
    size_t write_size = write(Response.getCgiFdForWrite(), body, 8);   

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    Response.mergeCgiResult(cgiOutput);
    int ResponseStatus = Response.ResponseStatus;
    EXPECT_EQ(500, ResponseStatus);
    close(Response.getCgiFd());
  } 
  // 0179
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/bad_cgi_002.cgi";
    client_.hmp.requestTarget_ = "/bad_cgi_002.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";
    client_.body = "name=ap2";
    client_.hmp.headers_["content-length"] = "8";

    Response Response(client_, config_);
    EXPECT_LE(3, Response.getCgiFd());
    EXPECT_LE(3, Response.getCgiFdForWrite());

    const char *body = "name=ap2";
    size_t write_size = write(Response.getCgiFdForWrite(), body, 8);   

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    Response.mergeCgiResult(cgiOutput);
    int ResponseStatus = Response.ResponseStatus;
    EXPECT_EQ(500, ResponseStatus);
    close(Response.getCgiFd());
  }
  // 0180
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/bad_cgi_003.cgi";
    client_.hmp.requestTarget_ = "/bad_cgi_003.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";
    client_.body = "name=ap2";
    client_.hmp.headers_["content-length"] = "8";

    Response Response(client_, config_);
    EXPECT_LE(3, Response.getCgiFd());
    EXPECT_LE(3, Response.getCgiFdForWrite());

    const char *body = "name=ap2";
    size_t write_size = write(Response.getCgiFdForWrite(), body, 8);   

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    Response.mergeCgiResult(cgiOutput);
    int ResponseStatus = Response.ResponseStatus;
    EXPECT_EQ(500, ResponseStatus);
    close(Response.getCgiFd());
  }
  // 0181
  {
    Client client_;
    client_.port = 8080;
    client_.host = "*";
    client_.hmp.method_ = httpMessageParser::POST;
    client_.hmp.absolutePath_ = "/bad_cgi_004.cgi";
    client_.hmp.requestTarget_ = "/bad_cgi_004.cgi";
    client_.hmp.headers_["host"] = "127.0.0.1";
    client_.ip = "127.0.0.1";
    client_.body = "name=ap2";
    client_.hmp.headers_["content-length"] = "8";

    Response Response(client_, config_);
    EXPECT_LE(3, Response.getCgiFd());
    EXPECT_LE(3, Response.getCgiFdForWrite());

    const char *body = "name=ap2";
    size_t write_size = write(Response.getCgiFdForWrite(), body, 8);   

    std::string cgiOutput;
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      read_size = read(Response.getCgiFd(), buf, sizeof(buf));
      if (read_size == 0)
        break;
      cgiOutput.append(buf);
    }
    Response.mergeCgiResult(cgiOutput);
    int ResponseStatus = Response.ResponseStatus;
    EXPECT_EQ(500, ResponseStatus);
    close(Response.getCgiFd());
  }
}