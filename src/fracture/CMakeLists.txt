file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(libfracture STATIC ${SRCS})

target_include_directories(libfracture PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(libfracture libxpoly libvem)

