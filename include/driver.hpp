#pragma once 
#include <string>

/***
 * Interface for any driver
 */
class WebDriver{
    public:
        virtual void get(const std::string& url) = 0;
        virtual ~WebDriver() {};
};