enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/googletest
        ${CMAKE_CURRENT_BINARY_DIR}/googletest)

include_directories(include)

set(TEST_SOURCE
        DummyTest.cpp
        ComponentTest.cpp
        ResultTest.cpp
        EventTest.cpp
        EventManagerTest.cpp
        EventDelegateTest.cpp
        ActionTest.cpp
        ActionResponseTest.cpp
        ActionResponseContainerTest.cpp
)

add_executable(${TEST_NAME} ${TEST_SOURCE})
target_link_libraries(${TEST_NAME} gtest_main ${LIBRARY_NAME})

add_test(
        NAME ${TEST_NAME}
        COMMAND ${TEST_NAME}
)