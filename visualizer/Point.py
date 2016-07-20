class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def draw(self, canvas, limits, color):
        canvas.create_oval(self.x, self.y, self.x + 3, self.y + 3, fill=color)

