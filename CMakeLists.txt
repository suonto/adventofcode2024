cmake_minimum_required(VERSION 3.10)
project(aoc_2024 VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable
add_executable(main_01 src/01/main.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

# GoogleTest
enable_testing()

# Add the test executable
add_executable(test_01 tests/01/test_main.cpp)

target_link_libraries(
  test_01
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_01)
