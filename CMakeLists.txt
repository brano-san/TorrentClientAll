cmake_minimum_required(VERSION 3.19)
project(TorrentClientAll LANGUAGES CXX)

set(LAUNCHER_DIR Launcher)
set(SOURCES_DIR src)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/build)
set(CMAKE_OBJECT_PATH ${CMAKE_SOURCE_DIR}/build/obj)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

file(GLOB_RECURSE CPP_SOURCES ${LAUNCHER_DIR}/*.cpp)
file(GLOB_RECURSE HPP_SOURCES ${LAUNCHER_DIR}/*.hpp)

qt_add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    ${CPP_SOURCES}
    ${HPP_SOURCES}
)

message(STATUS "Output dir - ${CMAKE_SOURCE_DIR}/build/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin/${PROJECT_NAME}_$<CONFIG>"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# Logger connect
set(ENABLE_DEBUG OFF)
add_subdirectory("${SOURCES_DIR}/Logger")
target_link_libraries(${PROJECT_NAME} PRIVATE Logger::Logger)
