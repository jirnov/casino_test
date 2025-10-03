if (MSVC)
    set(FREEGLUT_DIR "${CMAKE_SOURCE_DIR}/thirdparty/freeglut")
    add_library(freeglut STATIC IMPORTED)
    set_target_properties(freeglut PROPERTIES
        IMPORTED_LOCATION "${FREEGLUT_DIR}/lib/x64/freeglut.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${FREEGLUT_DIR}/include")
else()
    find_package(GLUT REQUIRED)
endif()
