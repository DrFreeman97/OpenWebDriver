set(
    WEBDRIVER_SRC_FILES
    src/opendriver.cpp
)

find_package(CURL CONFIG REQUIRED)
add_library(webdriver OBJECT ${WEBDRIVER_SRC_FILES})

target_include_directories(webdriver PUBLIC include) 
target_link_libraries(webdriver PUBLIC CURL::libcurl)
