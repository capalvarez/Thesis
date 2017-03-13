#include <fracture/numeric/BreakableVeamer.h>

BreakableVeamer::BreakableVeamer() {}

BreakableVeamer::BreakableVeamer(const Veamer& veamer) {
    this->DOFs = veamer.DOFs;
    this->elements = veamer.elements;
    this->conditions = veamer.getConditions();
    this->points = veamer.getPoints();
}

void BreakableVeamer::createElement(Polygon p) {
    polygon_to_element.insert(std::make_pair(p,elements.size()));
    Veamer::createElement(p);
}

void BreakableVeamer::replaceElement(Polygon old, std::vector<Polygon> newPolygons) {
    int to_remove = polygon_to_element[old];
    polygon_to_element.erase(old);

    elements.erase(elements.begin() + to_remove);

    for (int i = 0; i < newPolygons.size(); ++i) {
        createElement(newPolygons[i]);
    }
}

void BreakableVeamer::replaceElements(std::vector<Polygon> old, std::vector<Polygon> newPolygons, UniqueList<Point> points) {
    this->points = points;

    for (int i = 0; i < old.size(); ++i) {
        int to_remove = polygon_to_element[old[i]];
        polygon_to_element.erase(old[i]);

        elements.erase(elements.begin() + to_remove);
    }

    for (int i = 0; i < newPolygons.size(); ++i) {
        createElement(newPolygons[i]);
    }
}
