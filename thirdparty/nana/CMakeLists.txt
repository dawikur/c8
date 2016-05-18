CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(GTEST_BUILDER C CXX)

INCLUDE(ExternalProject)

ExternalProject_Add(nana
  GIT_REPOSITORY https://github.com/cnjinhao/nana.git
  GIT_TAG hotfix-1.3
  CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
             -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
             -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
             -DCMAKE_CXX_COMPILER_ID=GNU
             -DBUILD_GTEST=ON
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  INSTALL_COMMAND ""                                                           # disable installing
)

ExternalProject_Get_Property(nana source_dir)                                  # Specify include dir
set(NANA_INCLUDE_DIRS ${source_dir}/include PARENT_SCOPE)

ExternalProject_Get_Property(nana binary_dir)                                  # Specify MainTest's link libraries
set(NANA_LIBS_DIR ${binary_dir} PARENT_SCOPE)
