#include<http/curl_socket.hpp>
#include <curl/easy.h>


static int curl_sockets = 0;

CurlSocket::CurlSocket() : buffer(1024*1024,0)
{
    if(curl_sockets == 0){
        curl_global_init(CURL_GLOBAL_ALL);
    }
    _nativehandle = curl_easy_init();  
    curl_sockets++;
}

CurlSocket::~CurlSocket()
{
    curl_easy_cleanup(_nativehandle);
    curl_sockets--;
    if(curl_sockets == 0){
        curl_global_cleanup();
    }
}


