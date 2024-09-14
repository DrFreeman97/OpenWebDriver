#include "support/arguments_vector.hpp"
#include "support/functionals.hpp"
#include <alloca.h>
#include <sched.h>
#include <service.hpp>
#include <vector>
#ifdef _WIN32
#include <Windows.h>

void Service::start() {}

void Service::stop() {}

#endif

#ifdef __unix__
#include <unistd.h>
#include <csignal>

void Service::start() {
  process = fork();
  auto args = get_args().argv();
  char ** argv = static_cast<char**>(alloca(args.size()));
  for (int i = 0; i < args.size(); ++i) {
    argv[i] = const_cast<char*>(args[i].c_str());
  }
  if (process == 0) {
    execv(_servicePath.c_str(), argv);
  } else if (process == -1) {
    // this is an error
  }
  _isRunning = true;
}

void Service::stop() {
  if(_isRunning){
    process = kill(process, SIGINT);
  }
}


FirefoxService::FirefoxService()
    : Service("/usr/bin/geckodriver"),
      _firefoxPath("/usr/bin/firefox")
{
  _port = 4444;
}




#endif


ArgumentVector FirefoxService::get_args() {
  ArgumentVector vec{};
  vec.add_argument("--port",_port)
  .add_argument("--allow-hosts", join(_allowedHosts))
  .add_argument("--binary", _firefoxPath);
  return vec;
}