#include <alloca.h>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <curl/curl.h>
#include <curl/easy.h>
#include <http/http_socket.hpp>
#include <sstream>
#include <string>
#include <variant>

static int curl_sockets = 0;

size_t write_buffered(char *ptr, size_t size, size_t nmemb,
                      std::string *stringbuffer) {
  if (stringbuffer == NULL)
    return 0;
  stringbuffer->append(ptr,size*nmemb);
  return size * nmemb;
}

inline constexpr void set_default_opts(CURL *curl, const char *url,
                                       std::string *buffer) {

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buffered);
}

inline constexpr std::variant<std::string, CURLcode>
_return_default_buffer(CURLcode code, std::string *buffer) {
  if (code != CURLE_OK) {
    return code;
  }
  return std::string(*buffer);
}

#define return_default_buffer(code, buffer)                                    \
  return _return_default_buffer(code, buffer);

HttpSocket::HttpSocket() {
  if (curl_sockets == 0) {
    curl_global_init(CURL_GLOBAL_ALL);
  }
  _nativehandle = curl_easy_init();
  curl_sockets++;
}

std::variant<std::string, CURLcode>
HttpSocket::http_get(const std::string &url) {
  std::string buffer = std::string{};
  set_default_opts(_nativehandle, url.c_str(), &buffer);
  curl_easy_setopt(_nativehandle, CURLOPT_HTTPGET, 1);
  CURLcode res = curl_easy_perform(_nativehandle);
  curl_easy_reset(_nativehandle);
  return_default_buffer(res, &buffer);
}

std::variant<std::string, CURLcode>
HttpSocket::http_post(const std::string &url, const std::string &data) {
  std::string buffer = std::string{};
  set_default_opts(_nativehandle, url.c_str(), &buffer);
  curl_easy_setopt(_nativehandle, CURLOPT_POST, 1);
  curl_easy_setopt(_nativehandle, CURLOPT_POSTFIELDS, data.c_str());
  CURLcode res = curl_easy_perform(_nativehandle);
  curl_easy_reset(_nativehandle);
  return_default_buffer(res, &buffer);
}

std::variant<std::string, CURLcode>
HttpSocket::http_delete(const std::string &url, const std::string &data) {
  std::string buffer = std::string{};
  set_default_opts(_nativehandle, url.c_str(), &buffer);
  curl_easy_setopt(_nativehandle, CURLOPT_CUSTOMREQUEST, "DELETE");
  curl_easy_setopt(_nativehandle, CURLOPT_POSTFIELDS, data.c_str());
  CURLcode res = curl_easy_perform(_nativehandle);
  curl_easy_reset(_nativehandle);
  return_default_buffer(res, &buffer);
}

HttpSocket::~HttpSocket() {
  curl_easy_cleanup(_nativehandle);
  curl_sockets--;
  if (curl_sockets == 0) {
    curl_global_cleanup();
  }
}
