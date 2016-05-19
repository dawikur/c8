cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME_STR c8)
project(${PROJECT_NAME_STR} C CXX)

enable_testing()

if(NOT WIN32)
  set(warnings "-Wall -Wextra -Werror -Wpedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-rtti")
else()
  set(warnings "/W4 /WX")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /GR-")
endif()

find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
