cmake_minimum_required(VERSION 3.16)
project(BreakoutProject LANGUAGES C)

set(USE_DIRECTX OFF)

# Include the FetchContent module
include(FetchContent)

# Declare SDL2 as a FetchContent dependency
FetchContent_Declare(
  SDL2
  URL https://www.libsdl.org/release/SDL2-2.26.5.tar.gz
)

# Make SDL2 available to the project
FetchContent_MakeAvailable(SDL2)

# Create an executable target that links against SDL2
add_executable(Breakout main.c)
target_link_libraries(Breakout SDL2::SDL2main SDL2::SDL2-static)
