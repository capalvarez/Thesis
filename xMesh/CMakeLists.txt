include_directories(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(libxmesh STATIC ${SRCS})

target_link_libraries(libxmesh libxpoly)
target_include_directories(libxmesh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



