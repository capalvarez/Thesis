set(BASEPATH ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${BASEPATH})

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_subdirectory(delaunay/lib)
add_library(libxpoly STATIC ${SRCS})

target_link_libraries(libxpoly triangle)

target_include_directories(libxpoly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(xpolymain main.cpp)
target_link_libraries(xpolymain libxpoly)