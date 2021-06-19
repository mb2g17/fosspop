cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -lSDL2_image")
set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

# Sets include directory
include_directories(.)

# Create executable of tests
add_executable(${BINARY} ${TEST_SOURCES})

# Links libraries to tests
target_link_libraries(${BINARY} gtest Game Test Grid ${PROJECT_LIBS})

# Set up assets
add_custom_command(TARGET FossPop_Tests PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/tests/assets_test ${PROJECT_BINARY_DIR}/assets)