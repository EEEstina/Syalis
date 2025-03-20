cmake_minimum_required(VERSION 3.10)
project(syalis)

set(CMAKE_VERSION_MAKEFILE ON)
set(CMAKE_CXX_FLAG "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
include_directories(/usr/local/include)

link_directories(/usr/local/lib)

set(LIB_SRC
    syalis/log.cc
    syalis/util.cc
    syalis/config.cc
    )

add_library(syalis SHARED ${LIB_SRC})
#add_library(syalis STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES(syalis_static PROPERTIES OUTPUT_NAME "syalis")

add_executable(test tests/test.cc)
add_dependencies(test syalis)
target_link_libraries(test syalis yaml-cpp)

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config syalis)
target_link_libraries(test_config syalis yaml-cpp)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
