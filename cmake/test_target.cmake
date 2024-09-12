set(_TEST_SRC 

test/main.cpp
)

add_executable(webdriver_test ${_TEST_SRC})
target_link_libraries(webdriver_test PRIVATE webdriver)