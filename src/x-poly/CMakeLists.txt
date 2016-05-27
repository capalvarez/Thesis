file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(libxpoly STATIC ${SRCS} geometry/Vector.cpp geometry/Vector.h geometry/Point3D.cpp geometry/Point3D.h geometry/Triangle.cpp geometry/Triangle.h)
target_link_libraries(libxpoly triangle)

target_include_directories(libxpoly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})