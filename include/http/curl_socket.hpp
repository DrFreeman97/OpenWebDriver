#pragma once
#include <cstdint>
#include <curl/curl.h>
#include <string>

class CurlSocket{
    private:
    std::string buffer;
    CURL* _nativehandle;
    public:
    CurlSocket();
    std::string get(const std::string& url);
    std::string post(const std::string& url, const std::string& data);

    template<typename T>
    T get(const std::string& url);

    template<typename T>
    T post(const std::string& url, const T& data);

    inline const CURL* get_native_handle() const { return _nativehandle;}
    virtual ~CurlSocket();
};