cmake_minimum_required(VERSION 3.19)
project(TorrentClientAll LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE HPP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.hpp)
file(GLOB_RECURSE CPP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
list(FILTER CPP_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

if (NOT ${IS_TEST_PROJECT})
    message(STATUS "Building ${PROJECT_NAME} as main executable")
    add_executable (${PROJECT_NAME} main.cpp ${CPP_SOURCES} ${HPP_SOURCES})
else()
    message(STATUS "Building ${PROJECT_NAME} as executable")
    add_executable (${PROJECT_NAME} ${CPP_SOURCES} ${HPP_SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Widgets
)

set(ENABLE_DEBUG OFF)
add_subdirectory("${ROOT_DIR}/src/Logger" ${CMAKE_BINARY_DIR}/Src/Logger)
target_link_libraries(${PROJECT_NAME} PRIVATE Logger::Logger)

if (${IS_TEST_PROJECT})
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tests")
    target_link_libraries(${PROJECT_NAME} PRIVATE TestMain)
endif()

