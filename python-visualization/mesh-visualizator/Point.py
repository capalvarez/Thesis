class Point:
    def __init__(self, x, y, index=-1):
        self.x = x
        self.y = y
        self.index = index

    def draw(self, canvas, limits, color):
        y = float(canvas['height'])
        #if self.index==144 or self.index==86:
        #        or self.index==119 or self.index==120 or self.index==61 or self.index==60 or self.index==82 or self.index==85:
        #canvas.create_text(self.x, y-self.y,text=self.index, fill=color)

        #if self.index==168 or self.index==167 or self.index==157 or self.index==266 or self.index==268 or self.index==267 \
        #    or self.index==254 or self.index==261 or self.index==262 or self.index==292 or self.index==294 or self.index==295 \
        #    or self.index==293 or self.index==86 or self.index==144 or self.index==291 or self.index==290 or self.index==288 \
        #    or self.index==260 or self.index==259 or self.index==281 or self.index==285 or self.index==284 or self.index==139 \
        #    or self.index==120 or self.index==119 or self.index==118 or self.index==106 or self.index==46 or self.index==47:
            #canvas.create_text(self.x, y-self.y,text=self.index, fill="blue")
