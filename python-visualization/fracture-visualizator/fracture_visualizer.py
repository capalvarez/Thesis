from Tkinter import *

from FileReader import *
from Utils import draw_list, draw_polygons, draw_segments, WIDTH, HEIGHT

window = Tk()
frame = Frame(window)
frame.pack()

canvas = Canvas(window, width=WIDTH, height=HEIGHT, bg="white")

points, segments, polygons, crack_upper, crack_lower, limits = read_file("VerticalOneTip_step2.txt")

draw_list(points, canvas, limits, "red")
draw_polygons(polygons, canvas, points)
draw_segments(crack_upper, canvas, points)
draw_segments(crack_lower, canvas, points)

canvas.pack()
canvas.update()
canvas.postscript(file=FILE_PATH + "step2.ps", colormode='color')
window.mainloop()

