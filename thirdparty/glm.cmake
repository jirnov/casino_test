set(GLM_DIR "${PROJECT_SOURCE_DIR}/thirdparty/glm")
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${GLM_DIR}/include)
