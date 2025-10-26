cmake_minimum_required(VERSION 3.19)
project(TorrentClientAll LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE HPP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.hpp)
file(GLOB_RECURSE CPP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

if (NOT ${IS_TEST_PROJECT})
    message(STATUS "Building ${PROJECT_NAME} as main executable")
    add_executable (${PROJECT_NAME}
        ${CPP_SOURCES}
        ${HPP_SOURCES}
    )
else()
    message(STATUS "Building ${PROJECT_NAME} as executable")
    list(FILTER CPP_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")
    add_executable (${PROJECT_NAME}
        ${CPP_SOURCES}
        ${HPP_SOURCES}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Widgets
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

set(ENABLE_DEBUG OFF)
add_subdirectory("${THIRD_PARTY_DIR}/Logger" ${CMAKE_BINARY_DIR}/third_party/Logger)
target_link_libraries(${PROJECT_NAME} PRIVATE Logger::Logger)

if (${IS_TEST_PROJECT})
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tests")
    target_link_libraries(${PROJECT_NAME} PRIVATE TestMain)
endif()

