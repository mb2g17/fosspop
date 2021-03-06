# FossPop

[![Build Status](https://jenkins.matt-barnes.co.uk/buildStatus/icon?job=FossPop)](https://jenkins.matt-barnes.co.uk/job/FossPop/)
[![Available on GitHub](https://img.shields.io/badge/Available%20on-GitHub-white?logo=github)](https://github.com/mb2g17/fosspop)

## Table of contents

-   [General Info](#general-info)
-   [Setup](#setup)
-   [Images](#images)

# General Info

This project is a watered-down, free-and-open-source (FOSS) clone of the game HuniePop, created to test the waters of Emscripten and WebAssembly.

This clone takes out all the dating aspects of HuniePop, leaving just the puzzle gameplay.

# Setup

Prerequisites:

-   A C++ compiler (obviously)
-   CMake
-   Emscripten SDK
-   SDL2
-   SDL2_image

## Manually

### Project

```shell
mkdir cmake_build
cd cmake_build
cmake ../src -DCMAKE_TOOLCHAIN_FILE=<Emscripten toolchain file path>
make all
http-server dist
```

### Unit Tests

```shell
mkdir cmake_tests
cd cmake_tests
cmake ..
make all
./tests/FossPop_Tests
```

## Docker

### Project

### Unit Tests

```shell
docker build -t fosspop-tests -f Dockerfile.tests .
docker run fosspop-tests
```

# Images

Coming soon
