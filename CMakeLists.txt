cmake_minimum_required(VERSION 3.3)
project(Thesis C CXX)

set(SOURCE_DIR CMAKE_CURRENT_SOURCE_DIR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/x-poly/geometry/Point.cpp src/x-poly/geometry/Point.h src/x-poly/geometry/Polygon.cpp src/x-poly/geometry/Polygon.h src/x-poly/geometry/Region.cpp src/x-poly/geometry/Region.h src/x-poly/delaunay/DelaunayGenerator.h src/x-poly/delaunay/TriangleDelaunayGenerator.cpp src/x-poly/delaunay/TriangleDelaunayGenerator.h src/x-poly/converter/DelaunayVoronoiConverter.cpp src/x-poly/converter/DelaunayVoronoiConverter.h src/x-poly/geometry/generator/PointGenerator.h src/x-poly/geometry/generator/RandomPointGenerator.cpp src/x-poly/geometry/generator/RandomPointGenerator.h src/x-poly/geometry/generator/UniformPointGenerator.cpp src/x-poly/geometry/generator/UniformPointGenerator.h src/x-poly/geometry/Mesh.cpp src/x-poly/geometry/Mesh.h src/x-poly/geometry/Segment.cpp src/x-poly/geometry/Segment.h src/x-poly/geometry/Hole.cpp src/x-poly/geometry/Hole.h src/x-poly/geometry/geometryFunctions.cpp)
add_subdirectory(src/x-poly/delaunay/lib)
add_executable(Thesis ${SOURCE_FILES})
target_link_libraries(Thesis triangle)