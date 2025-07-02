file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_executable(Launcher ${GAME_SOURCES})

target_include_directories(Launcher PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/../engine/include
)

target_link_libraries(Launcher PRIVATE strix)
