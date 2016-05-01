CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(GTEST_BUILDER C CXX)

INCLUDE(ExternalProject)

ExternalProject_Add(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
             -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
             -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
             -Dgtest_force_shared_crt=ON
             -DBUILD_GTEST=ON
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  INSTALL_COMMAND ""                                                           # disable installing
)

ExternalProject_Get_Property(googletest source_dir)                            # Specify include dir
set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include PARENT_SCOPE)

ExternalProject_Get_Property(googletest binary_dir)                            # Specify MainTest's link libraries
set(GTEST_LIBS_DIR ${binary_dir}/googlemock/gtest PARENT_SCOPE)
