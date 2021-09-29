cmake_minimum_required(VERSION 3.10)

# Sets project name
project(FossPop_Tests)

# Sets include directory
include_directories(include)

# Finds SDL2 libraries
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_image REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2_mixer REQUIRED SDL2_mixer>=2.0.0)

# Adds project and test cases
add_subdirectory(src/game)
add_subdirectory(src/test)
add_subdirectory(src/grid)
add_subdirectory(src/assets)
add_subdirectory(tests)

# Adds googletest
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()