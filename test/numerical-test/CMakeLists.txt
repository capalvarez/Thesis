set(Main_SRCS NumericalTests.cpp NumericalTests.h main.cpp)

add_executable(numericaltests ${Main_SRCS})
target_link_libraries(numericaltests libvem)

