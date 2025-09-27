set(GLEW_ROOT "${PROJECT_SOURCE_DIR}/thirdparty/glew-2.1.0")
add_library(glew STATIC IMPORTED)
target_include_directories(glew INTERFACE "${GLEW_ROOT}/include")
set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${GLEW_ROOT}/lib/Release/x64/glew32.lib)
