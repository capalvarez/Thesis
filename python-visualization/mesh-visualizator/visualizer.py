from Tkinter import *
from FileReader import *
from Drawer import *


def draw_polygons(polygons, canvas, points):
    draw_list(polygons, canvas, points, "black")


def draw_segments(segments, canvas, points):
    draw_list(segments, canvas, points, "blue")

window = Tk()
frame = Frame(window)
frame.pack()

canvas = Canvas(window, width=900, height=700, bg="white")

points, segments, polygons, limits = read_file("second.txt")
#t_points, triangles, t_limits = read_triangulation("rosette.txt")

button = Button(frame, text="Draw Polygons", command=lambda p=polygons, c=canvas, ps=points: draw_polygons(p, c, ps))
button2 = Button(frame, text="Draw Segments", command=lambda s=segments, c=canvas, p=points: draw_segments(s, c, p))
button3 = Button(frame, text="Clear", command=lambda: canvas.delete("all"))

draw_list(points, canvas, limits,"red")
#draw_list(t_points, canvas, t_limits, "red")
#draw_list(triangles, canvas, t_points, "blue")

canvas.pack()
button.pack(side="right")
button2.pack(side="right")
button3.pack(side="right")

window.mainloop()

