cmake_minimum_required(VERSION 3.16)
project(optimizer-test VERSION 0.1)
set (CMAKE_CXX_STANDARD 11)

include_directories(../src/include /usr/local/include)

find_library(OPTIMIZER optimizer-lib /usr/local/lib)

add_executable(optimizer-test converge.cpp)
target_link_libraries(optimizer-test PUBLIC ${OPTIMIZER})