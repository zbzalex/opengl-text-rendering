cmake_minimum_required(VERSION 3.19)

project(PROJECT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

enable_language(C)
enable_language(CXX)

add_subdirectory(game)

find_package(OpenGL REQUIRED)
find_package(SDL2   REQUIRED)

add_executable(test
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/game/include
  ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(test
  PUBLIC
    game
)
