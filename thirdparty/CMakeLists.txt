cmake_minimum_required(VERSION 2.8)

add_subdirectory(gtest)
add_subdirectory(nana)

set(GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIRS} PARENT_SCOPE)
set(GTEST_LIBS_DIR ${GTEST_LIBS_DIR} PARENT_SCOPE)
