import sys


def read_file(file_name):
    file = open("C:\\Users\\Catalina\\" + file_name, "r")
    number_points = int(file.readline())
    x = set([])
    y = set([])
    u = [[] for i in range(0,11)]

    list_index = 0

    min_x = sys.maxsize
    max_x = -sys.maxsize - 1
    min_y = sys.maxsize
    max_y = -sys.maxsize - 1

    for i in range(number_points):
        line = file.readline().split()

        if max_x<float(line[0]):
            max_x = float(line[0])

        if max_y < float(line[1]):
            max_y = float(line[1])

        if min_x > float(line[0]):
            min_x = float(line[0])

        if min_y > float(line[1]):
            min_y = float(line[1])

        x.add(float(line[0]))
        y.add(float(line[1]))

        if i % 11 == 0 and i != 0:
            list_index += 1

        u[list_index].append(float(line[2])*1000000)

    limits = [min_x, max_x, min_y, max_y]

    return list(x),list(y),u





