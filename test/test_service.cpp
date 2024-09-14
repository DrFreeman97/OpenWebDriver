#include <gtest/gtest.h>
#include <service.hpp>

TEST(TestService, test_service_init){
    auto service = FirefoxService()
    .setFirefoxPath("firefox")
    .setDriverPath("geckodriver");

    service.start();
    ASSERT_NE(0, service.get_pid());
    service.stop();
}
