file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testxpoly ${SRCS})
TARGET_LINK_LIBRARIES(testxpoly
        libxpoly
        libgtest)

add_test(NAME testxpoly
        COMMAND testxpoly)