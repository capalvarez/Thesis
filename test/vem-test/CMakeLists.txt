file(GLOB_RECURSE SRCS *.cpp)

ADD_EXECUTABLE(testvem ${SRCS})
TARGET_LINK_LIBRARIES(testvem
        libvem
        libgtest)

add_test(NAME testvem
        COMMAND testvem)