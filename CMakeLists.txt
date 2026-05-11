cmake_minimum_required(VERSION 3.21)
project(RingBufferTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests ring_buffer_test.cpp)
target_link_libraries(run_tests GTest::gtest_main)