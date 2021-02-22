cmake_minimum_required(VERSION 3.10)

project(FossPop_Tests)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/tests)
set(CTEST_BINARY_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

file(GLOB files "test_*.cpp")

include(CTest)

foreach(file ${files})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})

    # Create executable of test case
    add_executable(${file_without_ext} ${file})

    # Links libraries to test case executable
    target_link_libraries(${file_without_ext} ${PROJECT_LIBS})

    # Add test
    add_test(NAME ${file_without_ext} COMMAND ${file_without_ext} WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

    # Sets timeout
    set_tests_properties(${file_without_ext}
        PROPERTIES
        TIMEOUT 120)
endforeach()