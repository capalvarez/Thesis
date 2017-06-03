class Point:
    def __init__(self, x, y, index=-1):
        self.x = x
        self.y = y
        self.index = index

    def draw(self, canvas, limits, color):
        y = float(canvas['height'])
        #if self.index==270 or self.index==254:
        #        or self.index==119 or self.index==120 or self.index==61 or self.index==60 or self.index==82 or self.index==85:
        canvas.create_text(self.x, y-self.y,text=self.index, fill=color)

        #if self.index==87 or self.index==266 or self.index==268 or self.index==269 or self.index==271 or self.index==270 \
            #or self.index==254 or self.index==286 or self.index==255 or self.index==256 or self.index==252 or self.index==251 \
            #or self.index==249 or self.index==130 or self.index==119 or self.index==120 or self.index==61 or self.index==60 \
            #or self.index==82 or self.index==85:
            #or self.index==46 or self.index==45 or self.index==44 or self.index==57:
            #canvas.create_text(self.x, y-self.y,text=self.index, fill="blue")
