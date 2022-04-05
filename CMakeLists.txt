cmake_minimum_required(VERSION 3.21)

set(PROJECT_NAME opengl_game)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp
        source/Renderer/ShaderManager.cpp
        source/Renderer/ShaderManager.h
        source/Assets/AssetsManager.cpp
        source/Assets/AssetsManager.h
        vendor/stb_image/stb_image.h source/Renderer/Texture2D.cpp source/Renderer/Texture2D.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(vendor/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/bin/assets
        )