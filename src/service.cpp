#include "support/arguments_vector.hpp"
#include "support/functionals.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <malloc.h>
#include <service.hpp>
#include <vector>

#ifdef _WIN32
#include <minwinbase.h>
#include <processthreadsapi.h>
#include <windows.h>
#include <winerror.h>

// use env variables to address driver and browser

void Service::start() {
  ZeroMemory(&process, sizeof(process));
  ZeroMemory(&process_startup, sizeof(process_startup));
  int ps = sizeof(process_startup);
  process_startup.cb = ps;
  auto args = get_service_args();
  auto argvector = args.argv();
  std::string commandline = _servicePath;
  for (auto &arg : argvector) {
    commandline += " " + arg;
  }

  auto res =
      CreateProcess(NULL, const_cast<char *>(commandline.c_str()), NULL, NULL,
                    false, 0, NULL, NULL, &process_startup, &process);
  if (!res) {
    // TODO error should throw?
  }
  _isRunning = true;
}

void Service::stop() {
  // TODO should manage errors
  TerminateProcess(process.hProcess, 0);
  WaitForSingleObject(process.hProcess, INFINITE);
  CloseHandle(process.hProcess);
  CloseHandle(process.hThread);
  _isRunning = false;
  return;
}

FirefoxService::FirefoxService() : Service() {}

#endif

#ifdef __unix__
#include <csignal>
#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>

void Service::start() {
  // check if service and browser exists
  if (!std::filesystem::exists(_servicePath)) {
    // TODO this is an error
    printf("Error executing driver");
  }
  process = fork();
  printf("Process forked");
  if (process == 0) {
    auto args = get_service_args().argv();
    char **argv = static_cast<char **>(alloca(args.size()));
    for (int i = 0; i < args.size(); ++i) {
      argv[i] = const_cast<char *>(args[i].c_str());
    }
    printf("Executing driver");
    execv(_servicePath.c_str(), argv);
  } else if (process == -1) {
    // TODO this is an error
  }
  if (waitpid(process, NULL, WNOWAIT) == -1) {
    _isRunning = false;
    // not running
  } else {
    _isRunning = true;
  }
}

void Service::stop() {
  if (_isRunning) {
    int stalock = 0;
    process = kill(process, SIGINT);
    waitpid(process, &stalock, WNOHANG);
  }
}

FirefoxService::FirefoxService() : Service() { _port = 4444; }

#endif

ArgumentVector FirefoxService::get_service_args() {
  ArgumentVector vec{};
  vec.add_argument("--port", _port)
      .add_argument("--allow-hosts", join(_allowedHosts));
  return vec;
}

Service::Service() : _servicePath() {}
