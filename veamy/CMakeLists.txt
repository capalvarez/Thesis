include_directories(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(libvem STATIC ${SRCS})

target_link_libraries(libvem libxpoly)
target_include_directories(libvem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



