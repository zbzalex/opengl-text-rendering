cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(game)

enable_language(CXX)
enable_language(C)

find_package(OpenGL REQUIRED)
find_package(SDL2   REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    /usr/local/opt/freetype/include/freetype2
    /usr/local/opt/glm/include
)

add_library(game
    SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SDLRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Text.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Sprite.cpp
)

target_link_libraries(game
    PUBLIC
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARY}
    /usr/local/opt/freetype/lib/libfreetype.dylib
)
