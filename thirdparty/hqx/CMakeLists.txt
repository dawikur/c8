cmake_minimum_required(VERSION 2.8)

add_library(hqx hqx-1.1/src/hq2x.c hqx-1.1/src/hq3x.c hqx-1.1/src/hq4x.c)

set(HQX_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
