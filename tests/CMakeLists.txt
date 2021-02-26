cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -lSDL2_image")
set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

# Create executable of tests
add_executable(${BINARY} ${TEST_SOURCES})

# Links libraries to tests
target_link_libraries(${BINARY} gtest Game Test ${PROJECT_LIBS})