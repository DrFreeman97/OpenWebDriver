#include <gtest/gtest.h>
#include <service.hpp>

TEST(TestService, test_service_init) {
  auto service =
      FirefoxService().setFirefoxPath("firefox").setDriverPath("geckodriver");

  service.start();
  service.stop();
}
