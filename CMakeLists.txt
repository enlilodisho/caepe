cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME caepe)
set(LIBRARY_NAME ${PROJECT_NAME})
set(TEST_NAME ${LIBRARY_NAME}_test)
option(BUILD_TESTS "Build tests" ON)

project(${PROJECT_NAME} VERSION 1.0
                        DESCRIPTION "Component Action Event Program Engine"
                        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()