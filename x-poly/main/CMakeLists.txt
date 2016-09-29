set(Main_SRCS main.cpp)

add_executable(xpolymain ${Main_SRCS})
target_link_libraries(xpolymain libxpoly)

