class Point:
    def __init__(self, x, y, index=-1):
        self.x = x
        self.y = y
        self.index = index

    def draw(self, canvas, limits, color):
        y = float(canvas['height'])

        #if self.index != -1:
        #    canvas.create_text(self.x, y-self.y,text=self.index, fill=color)
