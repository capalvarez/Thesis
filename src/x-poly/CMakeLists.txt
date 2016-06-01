file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(libxpoly STATIC ${SRCS} geometry/PolygonalHole.cpp geometry/PolygonalHole.h geometry/CircularHole.cpp geometry/CircularHole.h)
add_subdirectory(delaunay/lib)
target_link_libraries(libxpoly triangle)

target_include_directories(libxpoly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})