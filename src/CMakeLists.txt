include_directories(${PROJECT_SOURCE_DIR}/include/${LIBRARY_NAME})

set(SOURCE_FILES
    Dummy.cpp
    Component.cpp
    Result.cpp
    ComponentsManager.cpp
    EventHandler.cpp
    EventDelegate.cpp
)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)