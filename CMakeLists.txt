cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]' --use-preload-plugins --preload-file assets")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "dist")

# Sets project name
project(FossPop)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sets include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Adds libraries
add_subdirectory(src)

# Adds executable
add_executable(FossPop src/main.cpp)

# Links libraries with main executable
target_link_libraries(FossPop PUBLIC Main Game)

# Set output as JS file
set(CMAKE_EXECUTABLE_SUFFIX ".js")

# Set up files
add_custom_command(TARGET FossPop PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ../assets assets)
add_custom_command(TARGET FossPop POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ../public/* dist)