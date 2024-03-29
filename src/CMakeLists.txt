cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]' -s USE_SDL_MIXER=2 -s ALLOW_MEMORY_GROWTH=1 --use-preload-plugins --preload-file assets")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "dist")

# Sets project name
project(FossPop)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sets include directory
include_directories(../include)

# Adds libraries
add_subdirectory(game)
add_subdirectory(test)
add_subdirectory(grid)
add_subdirectory(assets)

# Adds executable
add_executable(FossPop main.cpp)

# Links libraries with main executable
target_link_libraries(FossPop PUBLIC Game Test Grid Assets)

# Set output as JS file
set(CMAKE_EXECUTABLE_SUFFIX ".js")

# Set up assets
add_custom_command(TARGET FossPop PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../assets ${PROJECT_BINARY_DIR}/assets)
add_custom_command(TARGET FossPop POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/../public/* ${PROJECT_BINARY_DIR}/dist)