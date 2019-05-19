cmake_minimum_required(VERSION 3.6)
project(OmnidirectionalCamera)

set(USE_CUDA ON)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp processor.cpp)
add_executable(OmnidirectionalCamera ${SOURCE_FILES})
#target_link_libraries(OmnidirectionalCamera ${OpenCV_LIBS})
target_link_libraries(OmnidirectionalCamera opencv_core opencv_imgcodecs)
if(USE_CUDA)
    target_compile_definitions(OmnidirectionalCamera PRIVATE USE_CUDA)
    target_link_libraries(OmnidirectionalCamera opencv_cudawarping)
endif()
