cmake_minimum_required(VERSION 3.16)
project(matrix)
set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_executable(matrix
        src/main.cpp)

#### GoogleTests ####
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(matrix_test
        test/row_test.cpp
)
target_link_libraries(matrix_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_test)