file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_library(libfracture STATIC ${SRCS})

target_include_directories(libfracture PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(libfracture libxpoly libvem)

