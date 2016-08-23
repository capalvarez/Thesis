class Segment:
    def __init__(self,p1,p2):
        self.p1 = p1
        self.p2 = p2

    def draw(self, canvas, points, color):
        P1 = points[self.p1]
        P2 = points[self.p2]

        canvas.create_line(P1.x,P1.y,P2.x,P2.y,fill=color)
