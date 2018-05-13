cmake_minimum_required(VERSION 3.6)
project(OmnidirectionalCamera)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)

set(SOURCE_FILES main.cpp processor.cpp viewer.cpp)
add_executable(OmnidirectionalCamera ${SOURCE_FILES})
target_include_directories(OmnidirectionalCamera PRIVATE OmnidirectionalCamera_autogen/include/)
target_link_libraries(OmnidirectionalCamera ${OpenCV_LIBS})
target_link_libraries(OmnidirectionalCamera Qt5::Widgets)
