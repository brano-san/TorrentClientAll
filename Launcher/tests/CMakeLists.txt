if (NOT TARGET GTest::gtest)
    message(FATAL_ERROR "Something went wrong. Need gtest target here")
endif()

file(GLOB_RECURSE CPP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB_RECURSE HPP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.hpp)

target_sources (${PROJECT_NAME} PRIVATE ${CPP_SOURCES} ${HPP_SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    GTest::gtest
    GTest::gtest_main
)
