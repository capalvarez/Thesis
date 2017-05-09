#include <fracture/numeric/BreakableVeamer.h>

struct greater{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};

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

void BreakableVeamer::createAndInsertElement(Polygon p, int index) {
    polygon_to_element.insert(std::make_pair(p, index));
    Veamer::insertElement(p, index);
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
    std::vector<int> toRemoveIndexes;

    for (Polygon p: old) {
        int to_remove = polygon_to_element[p];
        polygon_to_element.erase(p);

        toRemoveIndexes.push_back(to_remove);
    }

    std::sort(toRemoveIndexes.begin(), toRemoveIndexes.end(), greater());
    for (int r: toRemoveIndexes) {
        this->elements.erase(this->elements.begin()+ r);
    }

    createAndInsertElement(newPolygons[0], toRemoveIndexes.back());

    for (int i = 1; i < newPolygons.size(); ++i) {
        createElement(newPolygons[i]);
    }
}
