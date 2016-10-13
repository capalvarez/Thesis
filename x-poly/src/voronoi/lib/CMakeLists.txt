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

