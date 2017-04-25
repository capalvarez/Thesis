class Point:
    def __init__(self, x, y, index=-1):
        self.x = x
        self.y = y
        self.index = index

    def draw(self, canvas, limits, color):
        #canvas.create_oval(self.x, self.y, self.x + 3, self.y + 3, fill=color)
        y = float(canvas['height'])
        #canvas.create_text(self.x, y-self.y,text=self.index, fill=color)
