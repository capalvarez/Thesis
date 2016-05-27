file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testxpoly ${SRCS} testgeometryfunctions.cpp testtriangle.cpp testpolygon.cpp testvector.cpp testpolygon.h)

TARGET_LINK_LIBRARIES(testxpoly
        libxpoly
        libgtest)

add_test(NAME testxpoly
        COMMAND testxpoly)