cmake_minimum_required(VERSION 3.0.0)
project(nodepp VERSION 1.3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(NODEPP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# interface-target
add_library(nodepp INTERFACE)
target_include_directories(nodepp INTERFACE ${NODEPP_INCLUDE_DIR})