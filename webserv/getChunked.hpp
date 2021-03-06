#ifndef _GETCHUNKED_H_
#define _GETCHUNKED_H_

#include <iostream>
#include <string>
#include <cerrno>
#include "ft.hpp"
#include "recvData.hpp"

enum chunkStatus {GET_CHUNK_SIZE, GET_CHUNK_DATA, GET_CHUNK_CRLF};

// Clientクラスのメンバ変数bodyと、recvDataクラスを受け取って、chunkedなデータを結合し、bodyに格納する
// chunkedのデータ書式に従わない場合は501を返す
class getChunked {
 public:
  void setClientBody(std::string *clientBody);
  void setRecvData(recvData *r);
  int parseChunkedData();
  void clear();
  void setDebugLevel(int level);

 public:
  getChunked();
  ~getChunked();

 public:
  enum chunkStatus status_;
  std::string *clientBody_;
  recvData *r_;

 public:
  int hexstring2int(std::string chunksize);
  int hex2int(char c);

 private:
   std::string chunksize_;
   int debugLevel_;

};

#endif