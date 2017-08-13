from Tkinter import *

from FileReader import *
from Utils import draw_list, draw_polygons, draw_segments, WIDTH, HEIGHT

window = Tk()
frame = Frame(window)
frame.pack()

canvas = Canvas(window, width=WIDTH, height=HEIGHT, bg="white")

r_points, r_segments, r_polygons, r_limits = read_file("unicorn.txt")
#points, segments, polygons, limits = read_file("unicornRandom10.txt")
#t_points, triangles, t_limits = read_triangulation("unicornRandom10_triangles.txt")

#button = Button(frame, text="Draw Polygons", command=lambda p=polygons, c=canvas, ps=points: draw_polygons(p, c, ps))
#button2 = Button(frame, text="Draw Segments", command=lambda s=segments, c=canvas, p=points: draw_segments(s, c, p))
#button3 = Button(frame, text="Clear", command=lambda: canvas.delete("all"))

#draw_polygons(polygons, canvas, points)
#draw_list(points, canvas, limits, "red")
draw_segments(r_segments, canvas, r_points)
draw_list(r_points, canvas, r_limits, "red")
#draw_list(t_points, canvas, t_limits, "red")
#draw_list(triangles, canvas, t_points, "red")

canvas.pack()
#button.pack(side="right")
#button2.pack(side="right")
#button3.pack(side="right")

canvas.update()
canvas.postscript(file=FILE_PATH + "unicorn.ps", colormode='color')
window.mainloop()
