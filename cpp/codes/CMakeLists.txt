cmake_minimum_required(VERSION 3.22)
project(codes)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}
        ${CUDA_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include
        )
message(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_LIBRARIES})


add_executable(codes
        time_util.cpp)

target_link_libraries(codes ${OpenCV_LIBS})