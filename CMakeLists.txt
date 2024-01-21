cmake_minimum_required(VERSION 3.26)
project(minesweeper-raylib)

set(CMAKE_CXX_STANDARD 23)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/baz606/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

set(RAYLIB_GUI_VERSION 4.0)
find_package(raygui ${RAYLIB_GUI_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raygui_FOUND) # If there's none, fetch raygui
    include(FetchContent)
    FetchContent_Declare(
            raygui
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/baz606/raygui/archive/refs/tags/${RAYLIB_GUI_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raygui)
    if (NOT raygui_POPULATED) # Have we downloaded raygui yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raygui)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        # Copy over raygui.h over to raylib_SOURCE_DIR
        configure_file(
                ${raygui_SOURCE_DIR}/src/raygui.h ${raylib_SOURCE_DIR}/src
        )
    endif()
endif()



# Our Project

add_executable(${PROJECT_NAME} src/main.cpp
        src/Game.h
        src/Game.cpp
        src/components/RectangleMeshComponent.h
        src/components/RectangleMeshComponent.cpp
        src/actors/Actor.h
        src/actors/Actor.cpp
        src/actors/Cell.h
        src/actors/Cell.cpp
        src/components/Component.h
        src/components/Component.cpp
        src/actors/Grid.h
        src/actors/Grid.cpp
        src/components/DrawComponent.cpp
        src/components/DrawComponent.h
        src/components/TextComponent.cpp
        src/components/TextComponent.h
        src/components/LineMeshComponent.cpp
        src/components/LineMeshComponent.h
        src/components/animator/Animator.cpp
        src/components/animator/Animator.h
        src/components/animator/Animation.cpp
        src/components/animator/Animation.h
        src/components/animator/TransformAnimation.cpp
        src/components/animator/TransformAnimation.h
        src/components/animator/FlashingAnimation.cpp
        src/components/animator/FlashingAnimation.h
        src/components/SpriteComponent.cpp
        src/components/SpriteComponent.h
        src/components/BoxCollider.cpp
        src/components/BoxCollider.h
        src/actors/BackButton.cpp
        src/actors/BackButton.h
        src/actors/Logo.cpp
        src/actors/Logo.h
)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

#add_executable(raylib_test main.cpp)
