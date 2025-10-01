cmake_minimum_required(VERSION 4.0)
project(ArrayModifier)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        9706f75b8f91c52a3840cf5d878a7f37ea10ef00
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(ArrayModifier main.cpp functions.cpp header.h)

add_executable(Testing tests/tests.cpp functions.cpp header.h)
target_link_libraries(Testing GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(Testing)