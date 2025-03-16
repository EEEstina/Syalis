cmake_minimum_required(VERSION 3.10)
project(syalis)

set(CMAKE_VERSION_MAKEFILE ON)
set(CMAKE_CXX_FLAG "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c=+11 -Wall -Wno-deprecated -Warror -Wno-unused-function")

set(LIB_SRC
    syalis/log.cc
    syalis/util.cc
    )

add_library(syalis SHARED ${LIB_SRC})
#add_library(syalis STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES(syalis_static PROPERTIES OUTPUT_NAME "syalis")

add_executable(test tests/test.cc)
add_dependencies(test syalis)
target_link_libraries(test syalis)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
