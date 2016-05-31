set(Main_SRCS main.cpp)

add_executable(main ${Main_SRCS})
target_link_libraries(main libxpoly)
target_link_libraries(main libvem)
