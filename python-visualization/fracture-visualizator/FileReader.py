from Point import *
from Polygon import *
from Segment import *
import sys

from Utils import FILE_PATH, MIN_SCREEN


def read_file(file_name):
    readable_file = open(FILE_PATH + file_name, "r")
    number_points = int(readable_file.readline())
    points = []
    segments = []
    polygons = []
    crack = []

    min_x = sys.maxsize
    max_x = -sys.maxsize - 1
    min_y = sys.maxsize
    max_y = -sys.maxsize - 1

    for i in range(number_points):
        line = readable_file.readline().split()

        if max_x<float(line[0]):
            max_x = float(line[0])

        if max_y < float(line[1]):
            max_y = float(line[1])

        if min_x > float(line[0]):
            min_x = float(line[0])

        if min_y > float(line[1]):
            min_y = float(line[1])

        points.append(Point(float(line[0]), float(line[1]), i))

    number_segments = int(readable_file.readline())

    for i in range(number_segments):
        line = readable_file.readline().split()
        segments.append(Segment(int(line[0]), int(line[1])))

    limits = [min_x, max_x, min_y, max_y]

    diff_x = (max_x - min_x) * 1.0
    diff_y = (max_y - min_y) * 1.0

    ratio_a = diff_y / diff_x
    ratio_b = diff_x / diff_y

    if ratio_a > ratio_b:
        ratio = ratio_b
    else:
        ratio = ratio_a

    fixed_width = (MIN_SCREEN - 100) * ratio
    fixed_height = (MIN_SCREEN - 100) * ratio

    base_x = 50 + limits[0]
    base_y = 50 + limits[2]

    m_x = (fixed_width / (limits[1] - limits[0]))
    m_y = (fixed_height / (limits[3] - limits[2]))

    number_polygons = int(readable_file.readline())
    for i in range(number_polygons):
        line = readable_file.readline().split()
        cx = float(line[len(line) - 2])
        cy = float(line[len(line) - 1])

        cxP = base_x + m_x * cx
        cyP = base_y + m_y * cy

        polygons_points = line[0:len(line)-2]
        polygons.append(Polygon(list(map(lambda x: int(x), polygons_points)), Point(cxP, cyP), i))

    number_crack_segments = int(readable_file.readline())
    for i in range(number_crack_segments):
        line = readable_file.readline().split()
        crack.append(Segment(int(line[0]), int(line[1])))

    return list(map(
        lambda p, inner_limits=limits:
        Point(50 + inner_limits[0] + fixed_width / (inner_limits[1] - inner_limits[0]) * p.x, 50
              + inner_limits[2] + fixed_height / (inner_limits[3] - inner_limits[2]) * p.y, p.index),
        points)), segments, polygons, crack, limits


