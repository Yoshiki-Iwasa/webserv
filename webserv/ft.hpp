#ifndef _FT_H_
#define _FT_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <climits>
#include <iostream>

#define SUCCESS 1
#define FAILURE 0

void ft_dummy_response(int code, int socketFd);
std::string ft_inet_ntos(struct in_addr in);
std::string ft_make_dummy_response(int code);
bool ft_isctl(char c);
bool ft_isspase_and_htab(char c);
bool ft_issubdelims(char c);
bool ft_istchar(char c);
bool ft_istoken(std::string s);
bool ft_istspecials(char c);
bool ft_isunreserved(char c);
bool ft_isvchar(char c);
bool ft_istchar(char c);
std::string ft_itos(int nu);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memset(void *s, int c, size_t n);
void ft_print_vector_string(std::vector<std::string> vs);
std::string ReplaceString
(
    std::string String1   // 置き換え対象
  , std::string String2   // 検索対象
  , std::string String3   // 置き換える内容
);
std::vector<std::string> ft_split_use_find_first_of(std::string s, std::string d);
int ft_stoi(std::string s);
std::string ft_trim
(
    const std::string& string
  , const char* trimCharacterList
);

#endif