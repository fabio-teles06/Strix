cmake_minimum_required(VERSION 3.18)

project(sol)
add_library(sol INTERFACE)
target_include_directories(sol INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)