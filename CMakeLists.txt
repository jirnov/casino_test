cmake_minimum_required(VERSION 3.10)

project(CasinoTest)

include(thirdparty/glew.cmake)
include(thirdparty/freeglut.cmake)
include(thirdparty/stb.cmake)
include(thirdparty/glm.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

set(CASINO_SOURCES
    src/Application.cpp
    src/Button.cpp
    src/Camera.cpp
    src/FPSMetrics.cpp
    src/Game.cpp
    src/GlutCallbacks.cpp
    src/Image.cpp
    src/main.cpp
    src/Mesh.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/ShaderManager.cpp
    src/Sprite.cpp
    src/SpriteManager.cpp
    src/Texture.cpp
    src/Wheel.cpp)

set(CASINO_HEADERS
    src/Application.h
    src/Button.h
    src/Camera.h
    src/Forward.h
    src/FPSMetrics.h
    src/Game.h
    src/GlutCallbacks.h
    src/Image.h
    src/Mesh.h
    src/Renderer.h
    src/Shader.h
    src/ShaderManager.h
    src/Sprite.h
    src/SpriteManager.h
    src/Texture.h
    src/Wheel.h)

add_executable(${PROJECT_NAME} ${CASINO_HEADERS} ${CASINO_SOURCES})

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
    target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION GLM_ENABLE_EXPERIMENTAL)
    target_link_libraries(${PROJECT_NAME} freeglut glew OpenGL::GL stb glm)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION GLM_ENABLE_EXPERIMENTAL)
    target_link_libraries(${PROJECT_NAME} glut ${GLEW_LIBRARIES} OpenGL::GL stb glm)
endif()
