cmake_minimum_required(VERSION 3.18)

project(strix)
find_package(OpenGL REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(STRIX_EXPORT_SDK ON CACHE BOOL "Export header files when building")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/smolSDK")
file(MAKE_DIRECTORY "${OUTPUT_DIR}")

#libs
add_subdirectory(${LIBS_DIR}/glm)

# Platform specific settings
if (WIN32)
    set(PLATFORM "win64")
endif()

# engine library

add_library(strix SHARED
    src/platform/${PLATFORM}_platform.cpp
    src/strix_gl.cpp
)
target_include_directories(strix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(strix PRIVATE -DSTRIX_ENGINE_EXPORTS)
target_link_libraries(strix PRIVATE ${OPENGL_LIBRARY} glm)

if (STRIX_EXPORT_SDK)
    add_custom_command(TARGET strix POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}/include
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include/strix ${OUTPUT_DIR}/include/strix
    )
endif()

#build game dll
add_library(game SHARED
    demo/quad_demo.cpp
)
target_link_libraries(game PRIVATE strix)

# test executable
add_executable(strix_test
    src/strix_test.cpp
)
target_link_libraries(strix_test PRIVATE strix)