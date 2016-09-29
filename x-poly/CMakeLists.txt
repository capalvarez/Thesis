set(BASEPATH ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${BASEPATH})

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

include_directories(${BASEPATH}/include)
add_subdirectory(src/voronoi/lib)
add_library(libxpoly STATIC ${SRCS})

target_link_libraries(libxpoly triangle)

target_include_directories(libxpoly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(main)


