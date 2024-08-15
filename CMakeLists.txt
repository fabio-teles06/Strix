cmake_minimum_required(VERSION 3.18)

project(strix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform specific settings
if (WIN32)
    set(PLATFORM "win64")
endif()



add_library(strix SHARED
    src/platform/${PLATFORM}_platform.cpp
    src/strix_gl.cpp
)
target_include_directories(strix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(strix PRIVATE -DSTRIX_EXPORTS)
target_link_libraries(strix PRIVATE opengl32)

add_executable(strix_test
    src/strix_test.cpp
)

target_link_libraries(strix_test PRIVATE strix)