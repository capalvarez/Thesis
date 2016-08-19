#ifndef THESIS_VEAMER_H
#define THESIS_VEAMER_H

#include <models/Element.h>
#include <x-poly/models/Mesh.h>

class Veamer {
private:
    std::vector<Element> elements;
    std::vector<Point> points;
public:
    void loadData(Mesh m);
    void simulate();
};


#endif //THESIS_VEAMER_H
