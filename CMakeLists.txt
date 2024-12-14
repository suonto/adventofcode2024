cmake_minimum_required(VERSION 3.10)
project(aoc_2024 VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Create a static library from the application code
add_library(lib_01 STATIC src/01/solve.cpp)
add_library(lib_02 STATIC src/02/solve.cpp src/02/report.cpp src/02/range.cpp)
add_library(lib_03 STATIC src/03/solve.cpp src/03/instruction.cpp)
add_library(lib_04 STATIC src/04/solve.cpp src/04/letter.cpp src/directions.cpp src/pos.cpp)
add_library(lib_05 STATIC src/05/solve.cpp)

# Add the main executable
add_executable(main_01 src/01/main.cpp)
add_executable(main_02 src/02/main.cpp)
add_executable(main_03 src/03/main.cpp)
add_executable(main_04 src/04/main.cpp)
add_executable(main_05 src/05/main.cpp)

# link mains to lib
target_link_libraries(main_01 lib_01)
target_link_libraries(main_02 lib_02)
target_link_libraries(main_03 lib_03)
target_link_libraries(main_04 lib_04)
target_link_libraries(main_05 lib_05)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

# GoogleTest
enable_testing()

# Add the test executable
add_executable(test_01 tests/01/test_solve.cpp)
add_executable(test_02 tests/02/test_solve.cpp)
add_executable(test_03 tests/03/test_solve.cpp)
add_executable(test_04 tests/04/test_solve.cpp)
add_executable(test_05 tests/05/test_solve.cpp)

# Link test executables
target_link_libraries(test_01 GTest::gtest_main lib_01)
target_link_libraries(test_02 GTest::gtest_main lib_02)
target_link_libraries(test_03 GTest::gtest_main lib_03)
target_link_libraries(test_04 GTest::gtest_main lib_04)
target_link_libraries(test_05 GTest::gtest_main lib_05)

include(GoogleTest)
gtest_discover_tests(test_01)
gtest_discover_tests(test_02)
gtest_discover_tests(test_03)
gtest_discover_tests(test_04)
gtest_discover_tests(test_05)
