#ifndef THESIS_DELAUNAYVORONOICONVERTER_H
#define THESIS_DELAUNAYVORONOICONVERTER_H

#include <vector>
#include "../models/Mesh.h"
#include "../models/Segment.h"
#include "../models/Polygon.h"

class DelaunayVoronoiConverter {
private:
    std::vector<Segment> voronoiEdges;
    std::vector<Point> voronoiPoints;
    std::vector<Polygon> voronoiCells;

    void generateVoronoiEdge(int t1, int t2, std::vector<Polygon> triangles);
    void generateVoronoiCell(Point p);

public:
    DelaunayVoronoiConverter(Mesh m);
    ~DelaunayVoronoiConverter();

    Mesh getVoronoiMesh();
};


#endif //THESIS_DELAUNAYVORONOICONVERTER_H
