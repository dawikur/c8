cmake_minimum_required(VERSION 2.8)

set(PROJECT_EMULATOR_NAME ${PROJECT_NAME_STR})

file(GLOB EMULATOR_SRC_FILES *.cpp */*.cpp)

include_directories(${NANA_INCLUDE_DIRS})

add_executable(${PROJECT_EMULATOR_NAME} ${EMULATOR_SRC_FILES})
add_dependencies(${PROJECT_EMULATOR_NAME} nana)

if(NOT WIN32)
  target_link_libraries(${PROJECT_EMULATOR_NAME}
    ${NANA_LIBS_DIR}/libnana.a)
  target_link_libraries(${PROJECT_EMULATOR_NAME} X11 rt Xft atomic)
else()
  target_link_libraries(${PROJECT_EMULATOR_NAME}
    debug ${NANA_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}nana${CMAKE_FIND_LIBRARY_SUFFIXES}
    optimized ${NANA_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}nana${CMAKE_FIND_LIBRARY_SUFFIXES})
endif()

target_link_libraries(${PROJECT_EMULATOR_NAME} ${CMAKE_THREAD_LIBS_INIT})
