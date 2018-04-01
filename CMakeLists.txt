# Version guard
cmake_minimum_required (VERSION 3.1)
project(libdillpp VERSION 1.6 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(libdill 1.6 REQUIRED)
find_package (Threads)

include_directories(include)


# Set C++11/14 support
set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


add_library(dillpp SHARED
    dillpp.cpp
)

target_link_libraries(dillpp ${LIBDILL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


# Layout. This works for all platforms:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/include/
set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

add_executable(test_1 tests/test1.cpp)
target_link_libraries(test_1 dillpp)

