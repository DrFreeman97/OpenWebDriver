set(
    WEBDRIVER_SRC_FILES
    src/opendriver.cpp
    src/driver.cpp
    src/service.cpp
    src/options.cpp
    src/argument_vector.cpp
    src/functionals.cpp
    src/request.cpp
    src/http_socket.cpp
    src/items.cpp
)

find_package(CURL CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
add_library(webdriver STATIC ${WEBDRIVER_SRC_FILES})
target_compile_options(webdriver PRIVATE -fno-exceptions -Wall)
target_include_directories(webdriver PUBLIC include) 
target_link_libraries(webdriver PUBLIC CURL::libcurl nlohmann_json::nlohmann_json fmt::fmt)
