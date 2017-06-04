cmake_minimum_required(VERSION 3.6)
project(omnidirectional)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp ocam_functions.cpp)
add_executable(omnidirectional ${SOURCE_FILES})
target_link_libraries(omnidirectional ${OpenCV_LIBS})
