file(GLOB_RECURSE SRCS *.cpp)

ADD_EXECUTABLE(testutilites ${SRCS})
TARGET_LINK_LIBRARIES(testutilites
        libutilities
        libgtest)

add_test(NAME testutilities
        COMMAND testutilities)