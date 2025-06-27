file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_executable(Game ${GAME_SOURCES})

target_include_directories(Game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Game PRIVATE strix)
