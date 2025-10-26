cmake_minimum_required(VERSION 3.19)
project(TorrentClientAll LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE CPP_SOURCES ${LAUNCHER_DIR}/src/*.cpp)
file(GLOB_RECURSE HPP_SOURCES ${LAUNCHER_DIR}/src/*.hpp)

if (NOT ${IS_TEST_PROJECT})
    message(STATUS "Building ${PROJECT_NAME} as executable")
    add_executable (${PROJECT_NAME} ${CPP_SOURCES} ${HPP_SOURCES})
else()
    message(STATUS "Building ${PROJECT_NAME} as library")
    add_library (${PROJECT_NAME} STATIC ${CPP_SOURCES} ${HPP_SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Widgets
)

set(ENABLE_DEBUG OFF)
add_subdirectory("${SOURCES_DIR}/Logger")
target_link_libraries(${PROJECT_NAME} PRIVATE Logger::Logger)

if (${IS_TEST_PROJECT})
    add_subdirectory("${LAUNCHER_DIR}/tests")
endif()

