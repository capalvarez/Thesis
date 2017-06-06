class Polygon:
    def __init__(self, points, centroid, index):
        self.p = points
        self.centroid = centroid
        self.index = index

    def draw(self, canvas, points, color):
        y = float(canvas['height'])

        #if self.index == 140:
        #    color = "green"

        for i in range(len(self.p)):
            p1 = points[self.p[i]]
            p2 = points[self.p[(i+1)%len(self.p)]]

            canvas.create_line(p1.x, y-p1.y, p2.x, y-p2.y, fill=color)
            #if self.index == 118 :
                #canvas.create_text(self.centroid.x, y-self.centroid.y, text=self.index, fill="red")

            #canvas.create_text(self.centroid.x, y-self.centroid.y, text=self.index)

