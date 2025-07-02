file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(strix SHARED ${ENGINE_SOURCES})

target_include_directories(strix PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_definitions(strix PRIVATE -DSTRIX_ENGINE_EXPORTS)

if (WIN32)
    target_compile_definitions(strix PRIVATE -D PLATFORM_WINDOWS)
elseif (UNIX)
    target_compile_definitions(strix PRIVATE -D PLATFORM_UNIX)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()