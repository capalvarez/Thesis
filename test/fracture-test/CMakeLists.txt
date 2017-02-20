file(GLOB_RECURSE SRCS *.cpp)

ADD_EXECUTABLE(testfracture ${SRCS})
TARGET_LINK_LIBRARIES(testfracture
        libfracture
        libgtest)

add_test(NAME testfracture
        COMMAND testfracture)