cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]' --use-preload-plugins --preload-file assets")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/dist")

# Sets project name
project(FossPop)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

# Adds executable
add_executable(FossPop src/main.cpp)

target_link_libraries(FossPop PUBLIC Main Game)

set(CMAKE_EXECUTABLE_SUFFIX ".html")

include_directories(${PROJECT_SOURCE_DIR}/include)