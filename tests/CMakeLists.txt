cmake_minimum_required(VERSION 3.19)
project(TestMain LANGUAGES CXX)

enable_testing()

file(GLOB_RECURSE TEST_MAIN_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${TEST_MAIN_SOURCES})

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/..)    

set(GOOGLE_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/googletest)
add_subdirectory(${GOOGLE_TEST_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::gtest
    GTest::gtest_main
)

set(IS_TEST_PROJECT TRUE)
add_subdirectory(${ROOT_DIR} ${CMAKE_BINARY_DIR}/Tests/TorrentClientAll)
