cmake_minimum_required(VERSION 3.10)

project(CasinoTest)

include(thirdparty/glew.cmake)
include(thirdparty/stb.cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(freeglut REQUIRED)

add_executable(casino_test main.cpp)
target_link_libraries(casino_test PRIVATE OpenGL::GL glew stb FreeGLUT::freeglut_static)
