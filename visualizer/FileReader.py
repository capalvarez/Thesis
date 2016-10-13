from Point import *
from Polygon import *
from Segment import *
import sys


def read_file(file_name):
    file = open("C:\\Users\\Catalina\\" + file_name, "r")
    number_points = int(file.readline())
    points = []
    segments = []
    polygons = []

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

        points.append(Point(float(line[0]), float(line[1])))

    number_segments = int(file.readline())

    for i in range(number_segments):
        line = file.readline().split()
        segments.append(Segment(int(line[0]), int(line[1])))

    number_polygons = int(file.readline())
    for i in range(number_polygons):
        line = file.readline().split()
        polygons.append(Polygon(list(map(lambda x: int(x), line))))

    limits = [min_x, max_x, min_y, max_y]

    return list(map(
        lambda p, limits=limits: Point(50 + limits[0] + 800 / (limits[1] - limits[0]) * p.x, 50 + limits[2] + 600 / (limits[3] - limits[2]) * p.y), points)), segments, polygons, limits


def read_triangulation(file_name):
    file = open("/home/cata/" + file_name, "r")
    number_points = int(file.readline())
    points = []
    triangles = []

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

        points.append(Point(float(line[0]), float(line[1])))

    number_triangles = int(file.readline())
    for i in range(number_triangles):
        line = file.readline().split()
        triangles.append(Polygon(list(map(lambda x: int(x), line))))

    limits = [min_x, max_x, min_y, max_y]

    return list(map(
        lambda p, limits=limits: Point(50 + limits[0] + 800 / (limits[1] - limits[0]) * p.x, 50 + limits[2] + 600 / (limits[3] - limits[2]) * p.y), points)), triangles, limits


