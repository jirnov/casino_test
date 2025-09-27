set(STB_ROOT "${PROJECT_SOURCE_DIR}/thirdparty/stb")
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${STB_ROOT}/include)
