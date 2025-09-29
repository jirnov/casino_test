set(STB_DIR "${PROJECT_SOURCE_DIR}/thirdparty/stb")
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${STB_DIR}/include)
