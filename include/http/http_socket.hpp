#pragma once
#include <cstdint>
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <variant>

class HttpSocket{
    private:
    CURL* _nativehandle;
    public:
    HttpSocket();
    std::variant<std::string,CURLcode> http_get(const std::string& url);
    std::variant<std::string,CURLcode> http_post(const std::string& url, const std::string& data);
    std::variant<std::string,CURLcode> http_put(const std::string& url, const std::string&data);
    std::variant<std::string,CURLcode> http_delete(const std::string& url, const std::string&data);

    template<typename T>
    T http_get(const std::string& url);

    template<typename T>
    T http_post(const std::string& url, const T& data);

    inline const CURL* get_native_handle() const { return _nativehandle;}
    virtual ~HttpSocket();

};