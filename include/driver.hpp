#pragma once 
#include "service.hpp"
#include <memory>
#include <string>
#include "options.hpp"
/***
 * Interface for any driver
 */
class WebDriver{ 
    private:
    std::unique_ptr<Service> _service{};
    std::unique_ptr<Options> _options{};
    public:
        WebDriver(std::unique_ptr<Service> service, std::unique_ptr<Options> options);
        virtual void get(const std::string& url);
        inline const std::unique_ptr<Service>& get_service() const{return _service;}
        inline const std::unique_ptr<Options>& get_options() const{return _options;}
        virtual void open() = 0;
        virtual void close() = 0;
        virtual ~WebDriver();
};

class Firefox: WebDriver{
    public:


};