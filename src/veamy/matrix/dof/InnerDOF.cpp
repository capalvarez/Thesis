#include <models/integration/IntegrationPolygon.h>
#include "InnerDOF.h"


double InnerDOF::getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p) {
    IntegrationPolygon polygon (p.getPoints(), points);



}

