
find_package(OpenGL REQUIRED)

if (WIN32)
    set(PLATFORM_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/win64_platform.cpp
    )
elseif (UNIX)
    set(PLATFORM_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/unix_platform.cpp
    )
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/*.hpp
)

add_library(strix SHARED ${ENGINE_SOURCES} ${PLATFORM_SOURCES})
target_include_directories(strix PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(strix PRIVATE ${OPENGL_LIBRARY})
target_compile_definitions(strix PRIVATE -DSTRIX_ENGINE_EXPORTS)
