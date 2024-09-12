#pragma once
#include <sched.h>
#include <string>
/**
 * @brief Class for all service, usually this identifies the bridge to start
 * 
 */
class Service{
    private:
    bool _isRunning = false;
    std::string _binPath{};
    pid_t process = -1;
    public:
    virtual void start();
    virtual void stop();
    virtual const char** get_args() = 0;
    Service(const std::string path);
};


