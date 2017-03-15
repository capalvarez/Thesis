class Segment:
    def __init__(self,p1,p2):
        self.p1 = p1
        self.p2 = p2

    def draw(self, canvas, points, color):
        y = float(canvas['height'])

        P1 = points[self.p1]
        P2 = points[self.p2]

        canvas.create_line(P1.x,y-P1.y,P2.x,y-P2.y,fill=color)
