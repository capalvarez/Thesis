from Tkinter import *

from FileReader import *
from Utils import draw_list, draw_polygons, draw_segments, WIDTH, HEIGHT

window = Tk()
frame = Frame(window)
frame.pack()

canvas = Canvas(window, width=WIDTH, height=HEIGHT, bg="white")

points, segments, polygons, crack, limits = read_file("squareUniform_step1.txt")

draw_list(points, canvas, limits, "red")
draw_polygons(polygons, canvas, points)
draw_segments(crack, canvas, points)

canvas.pack()

window.mainloop()

