cmake_minimum_required(VERSION 3.10)
project(ComputationalGemoetry)

set(CMAKE_CXX_STANDARD 11)
set(OPENCV_DIR "/usr/local/OpenCV-3.4")

include_directories(${OPENCV_DIR}/include ./)
link_directories(${OPENCV_DIR}/lib)


add_executable(ComputationalGemoetry Unit_Test/Heap_test.cpp)
target_link_libraries(ComputationalGemoetry opencv_core opencv_highgui opencv_imgproc)