#include <sched.h>
#include <service.hpp>
#ifdef _WIN32
#include <Windows.h>

void Service::start() {}

void Service::stop() {}

#endif

#ifdef __unix__
#include <unistd.h>

void Service::start() {
  process = fork();
  if (process == 0) {
    execv(_binPath.c_str(), const_cast<char *const *>(get_args()));
  } else if (process == -1) {
    // this is an error
  }
}

void Service::stop() {}

#endif