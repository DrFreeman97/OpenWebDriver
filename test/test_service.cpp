#include <gtest/gtest.h>
#include <service.hpp>


#define DOMAIN(a) EXPANSION(a)
#define EXPANSION(a) #a

#ifdef TEST_BROWSER_PATH
constexpr const char* browserpath = DOMAIN(TEST_BROWSER_PATH);
#else 
constexpr const char* browserpath = "/usr/bin/firefox";
#endif
#ifdef  TEST_SERVICE_PATH
constexpr const char* servicepath = DOMAIN(TEST_SERVICE_PATH);
#else 
constexpr const char* servicepath = "/usr/bin/geckodriver";
#endif



TEST(TestService, test_service_init) {
  FirefoxService service = FirefoxService();
  service.setDriverPath(servicepath);
  service.start();
  service.stop();
}
