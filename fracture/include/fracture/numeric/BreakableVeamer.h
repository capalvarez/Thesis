#ifndef THESIS_BREAKABLEVEAMER_H
#define THESIS_BREAKABLEVEAMER_H

#include <veamy/Veamer.h>

class BreakableVeamer: public Veamer{
private:
    std::unordered_map<Polygon, int, PolygonHasher> polygon_to_element;
public:
    BreakableVeamer();
    BreakableVeamer(const Veamer& veamer);

    virtual void createElement(Polygon p);
    void createAndInsertElement(Polygon p, int index);
    void replaceElement(Polygon old, std::vector<Polygon> newPolygons);
    void replaceElements(std::vector<Polygon> old, std::vector<Polygon> newPolygons, UniqueList<Point> points);
    void printInFile(std::string fileName);
};

#endif
