file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_library(strix STATIC ${ENGINE_SOURCES})

target_include_directories(strix PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link com libs externas (ajuste conforme suas dependências reais)
#    target_link_libraries(strix PUBLIC
#        glfw
#        glad
#        glm
#        lua
#    )

# Macro de compilação cross-platform
target_compile_definitions(strix PUBLIC STRIX_BUILD)