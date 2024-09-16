#pragma once
#include "support/arguments_vector.hpp"
#include <string>
#include <vector>
#ifdef _WIN32
#include <processthreadsapi.h>
#elif __unix__
#include <sched.h>
#endif

/**
 * @brief Class for all service, usually this identifies the bridge to start
 *
 */
struct Service {
#ifdef _WIN32
private:
  PROCESS_INFORMATION process;
  STARTUPINFO process_startup;
#elif __unix__
private:
  pid_t process;
#endif
private:
  bool _isRunning = false;

protected:
  int _port = 0;
  std::string _host{};
  virtual ArgumentVector get_args() = 0;
  std::string _servicePath{};
  std::string _browserPath{};
  Service(const std::string &driverpath, const std::string &browserpath);

public:
  virtual void start();
  virtual void stop();
  inline Service &setBrowserPath(const std::string path) {
    _browserPath = path;
    return *this;
  };
  inline Service &setHost(const std::string host) {
    _host = host;
    return *this;
  };
  inline Service &setPort(int port) {
    _port = port;
    return *this;
  };
};

struct FirefoxService : Service {
private:
  std::vector<std::string> _allowedHosts{"localhost"};
  std::string _firefoxPath;

protected:
  ArgumentVector get_args() override;

public:
  FirefoxService();

  inline FirefoxService &setDriverPath(std::string path) {
    _servicePath = path;
    return *this;
  }

  inline FirefoxService &setPort(int port) {
    _port = port;
    return *this;
  }

  inline FirefoxService &addAllowedHosts(std::string host) {
    _allowedHosts.push_back(host);
    return *this;
  }

  inline FirefoxService &setFirefoxPath(std::string path) {
    _firefoxPath = path;
    return *this;
  }
};