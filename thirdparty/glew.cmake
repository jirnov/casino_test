set(GLEW_DIR "${PROJECT_SOURCE_DIR}/thirdparty/glew-2.1.0")
add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION "${GLEW_DIR}/lib/Release/x64/glew32.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${GLEW_DIR}/include")
