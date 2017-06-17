cmake_minimum_required(VERSION 3.6)
project(OmnidirectionalCamera)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp ocam_functions.cpp processor.cpp viewer.cpp)
add_executable(OmnidirectionalCamera ${SOURCE_FILES})
target_link_libraries(OmnidirectionalCamera Qt5::Widgets)
target_link_libraries(OmnidirectionalCamera ${OpenCV_LIBS})
