cmake_minimum_required(VERSION 3.10)

# Sets project name
project(FossPop_Tests)

# Sets include directory
include_directories(include)

# Adds project and test cases
add_subdirectory(src/game)
add_subdirectory(src/test)
add_subdirectory(src/grid)
add_subdirectory(tests)

# Adds googletest
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()