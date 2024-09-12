set(_TEST_SRC 

test/main.cpp
)

find_package(GTest REQUIRED)
add_executable(webdriver_test ${_TEST_SRC})
target_link_libraries(webdriver_test PRIVATE webdriver GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)