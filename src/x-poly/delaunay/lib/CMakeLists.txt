ADD_CUSTOM_TARGET(triangle.o
        COMMAND ${CMAKE_MAKE_PROGRAM} trilibrary
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/x-poly/delaunay/lib)

add_library(triangle STATIC triangle.o)
SET_SOURCE_FILES_PROPERTIES(
        triangle.o
        PROPERTIES
        EXTERNAL_OBJECT true
        GENERATED true
)
SET_TARGET_PROPERTIES(
        triangle
        PROPERTIES
        LINKER_LANGUAGE C
)
target_include_directories(triangle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

