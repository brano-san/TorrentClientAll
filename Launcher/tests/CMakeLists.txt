if (NOT TARGET GTest::gtest)
    message(FATAL_ERROR "Something went wrong. Need gtest target here")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/build)
set(CMAKE_OBJECT_PATH ${CMAKE_SOURCE_DIR}/build/obj)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE CPP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB_RECURSE HPP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.hpp)

target_sources (${PROJECT_NAME} PRIVATE ${CPP_SOURCES} ${HPP_SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    GTest::gtest
    GTest::gtest_main
)
