#pragma once
#include "support/arguments_vector.hpp"
#include <sched.h>
#include <string>
#include <vector>
/**
 * @brief Class for all service, usually this identifies the bridge to start
 *
 */
struct Service {
private:
  bool _isRunning = false;
  pid_t process = -1;

protected:
  int _port = 0;
  std::string _host{};
  virtual ArgumentVector get_args() = 0;
  std::string _servicePath{};
  std::string _browserPath{};

public:
  virtual void start();
  virtual void stop();
  Service(const std::string path);
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
  inline pid_t get_pid() const { return process; }
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