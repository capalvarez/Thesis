set(BASEPATH ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${BASEPATH})

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.h  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

include_directories(${BASEPATH}/include/lib)
include_directories(${BASEPATH}/include)
add_library(libutilities STATIC ${SRCS})

target_include_directories(libutilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(libutilities PROPERTIES LINKER_LANGUAGE CXX)


