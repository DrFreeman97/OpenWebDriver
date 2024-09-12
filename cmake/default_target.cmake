set(
    WEBDRIVER_SRC_FILES
    src/opendriver.cpp
    src/driver.cpp
    src/service.cpp
    src/options.cpp
)

find_package(CURL CONFIG REQUIRED)
add_library(webdriver STATIC ${WEBDRIVER_SRC_FILES})
target_compile_options(webdriver PRIVATE -fno-exceptions -Wall)
target_include_directories(webdriver PUBLIC include) 
target_link_libraries(webdriver PUBLIC CURL::libcurl)
