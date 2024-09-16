#include "support/arguments_vector.hpp"
#include "support/functionals.hpp"
#include <cstddef>
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
  auto res =
      CreateProcess(NULL, const_cast<char *>(_browserPath.c_str()), NULL, NULL,
                    false, 0, NULL, NULL, &process_startup, &process);
  if (!res) {
    // error should throw?
  }
  _isRunning = true;
}

void Service::stop() {
  // should manage errors
  TerminateProcess(process.hProcess, 0);
  WaitForSingleObject(process.hProcess, INFINITE);
  CloseHandle(process.hProcess);
  CloseHandle(process.hThread);
  _isRunning = false;
  return;
}

FirefoxService::FirefoxService()
    : Service("C:/Geckodriver",
              "C:/Program Files/Mozilla Firefox/firefox.exe") {}

#endif

#ifdef __unix__
#include <csignal>
#include <sched.h>
#include <unistd.h>

void Service::start() {
  process = fork();
  auto args = get_args().argv();
  char **argv = static_cast<char **>(alloca(args.size()));
  for (int i = 0; i < args.size(); ++i) {
    argv[i] = const_cast<char *>(args[i].c_str());
  }
  if (process == 0) {
    execv(_servicePath.c_str(), argv);
  } else if (process == -1) {
    // this is an error
  }
  _isRunning = true;
}

void Service::stop() {
  if (_isRunning) {
    process = kill(process, SIGINT);
  }
}

FirefoxService::FirefoxService()
    : Service("/usr/bin/geckodriver"), _firefoxPath("/usr/bin/firefox") {
  _port = 4444;
}

#endif

ArgumentVector FirefoxService::get_args() {
  ArgumentVector vec{};
  vec.add_argument("--port", _port)
      .add_argument("--allow-hosts", join(_allowedHosts))
      .add_argument("--binary", _firefoxPath);
  return vec;
}