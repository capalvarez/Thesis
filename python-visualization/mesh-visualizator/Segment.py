class Segment:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2

    def draw(self, canvas, points, color):
        y = float(canvas['height'])

        point_1 = points[self.p1]
        point_2 = points[self.p2]

        #if (self.p1 == 144 and self.p2 ==86) or (self.p2 == 144 and self.p1 ==86):
        #    canvas.create_line(point_1.x, y-point_1.y, point_2.x, y-point_2.y, fill="red")
        #else:
        canvas.create_line(point_1.x, y-point_1.y, point_2.x, y-point_2.y, fill=color)
