cmake_minimum_required(VERSION 3.0)

project(hello_openCL)

find_package(OpenCL REQUIRED)
find_package(OpenCV REQUIRED)


add_subdirectory(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/kernel/ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/kernel)

add_executable(hello_openCL helloOpencl.cpp)

target_include_directories(hello_openCL PUBLIC  ${OpenCV_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS})
target_link_libraries(hello_openCL hello ${OpenCL_LIBRARY} ${OpenCV_LIBS} )
