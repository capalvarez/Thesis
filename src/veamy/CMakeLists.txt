file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(libvem STATIC ${SRCS})

target_include_directories(libvem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(libvem libxpoly)

add_executable(vemtest test.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)