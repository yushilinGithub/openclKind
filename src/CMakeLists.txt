cmake_minimum_required(VERSION 3.0)

file(GLOB SOURCE_FILE hello.cpp)
file(GLOB HEADER_FILE hello.hpp)


add_library(hello STATIC ${SOURCE_FILE} ${HEADER_FILE})
#target_include_directories(hello PUBLIC ${CMAKE_CURRENT_LIST_DIR})
