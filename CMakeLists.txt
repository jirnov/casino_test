cmake_minimum_required(VERSION 3.10)

project(CasinoTest)

include(thirdparty/glew.cmake)
include(thirdparty/freeglut.cmake)
include(thirdparty/stb.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} freeglut glew OpenGL::GL stb)
    target_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)
endif()
