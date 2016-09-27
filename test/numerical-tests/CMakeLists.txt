file(GLOB_RECURSE SRCS *.cpp)

ADD_EXECUTABLE(numericaltests ${SRCS})
TARGET_LINK_LIBRARIES(numericaltests
        libxpoly
        libvem)
