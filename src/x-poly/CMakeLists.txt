file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(libxpoly STATIC ${SRCS})
target_link_libraries(libxpoly triangle)

target_include_directories(libxpoly PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})