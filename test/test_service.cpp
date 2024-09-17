#include <chrono>
#include <cstdio>
#include <curl/curl.h>
#include <gtest/gtest.h>
#include <service.hpp>
#include <http/http_socket.hpp>
#include <string>
#include <thread>
#include <variant>

#define DOMAIN(a) EXPANSION(a)
#define EXPANSION(a) #a

#ifdef TEST_BROWSER_PATH
constexpr const char *browserpath = DOMAIN(TEST_BROWSER_PATH);
#else
constexpr const char *browserpath = "/usr/bin/firefox";
#endif
#ifdef TEST_SERVICE_PATH
constexpr const char *servicepath = DOMAIN(TEST_SERVICE_PATH);
#else
constexpr const char *servicepath = "/usr/bin/geckodriver";
#endif

TEST(TestService, test_service_init) {
  auto http = HttpSocket();
  FirefoxService service = FirefoxService();
  service.setDriverPath(servicepath);
  service.start();
  //test reachability of the service
  auto response = http.http_get("http://localhost:4444/status");
  if(std::holds_alternative<std::string>(response)){
    printf("gecko response: %s \n",std::get<std::string>(response).c_str());
    SUCCEED();
  }
  else{
    printf("Test failed with code %d \n",std::get<CURLcode>(response));
    FAIL();
  }
  // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  service.stop();
}
