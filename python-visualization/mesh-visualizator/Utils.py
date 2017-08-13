FILE_PATH = "C:\\Users\\Catalina\\"
HEIGHT = 700
WIDTH = 700
MIN_SCREEN = HEIGHT if HEIGHT < WIDTH else WIDTH


def draw_list(object_list, canvas, other, color):
    for l in object_list:
        l.draw(canvas, other, color)


def draw_polygons(polygons, canvas, points):
    draw_list(polygons, canvas, points, "black")


def draw_segments(segments, canvas, points):
    draw_list(segments, canvas, points, "black")
