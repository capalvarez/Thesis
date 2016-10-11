#include <veamy/matrix/integration/IntegrationPolygon.h>

IntegrationPolygon::IntegrationPolygon(std::vector<int> index, std::vector<Point> points) : Polygon(index,points){}

std::vector<IntegrationTriangle> IntegrationPolygon::triangulate(std::vector<IntegrationTriangle>& triangles, std::vector<Point>& p) {
    std::vector<int> pointList = this->getPoints();

    while(pointList.size()>=3){
        IntegrationTriangle ear = getEar(p, pointList);
        if(ear.isNull()){
            break;
        }
        triangles.push_back(ear);
    }

    return triangles;
}

double IntegrationPolygon::integrate(IntegrationFunction* f, std::vector<Point> points) {
    double result = 0;
    std::vector<IntegrationTriangle> triangles;
    triangulate(triangles, points);

    for(int i=0;i<triangles.size();i++){
        result += triangles[i].integrate(f, points);
    }

    return result;
}


IntegrationTriangle IntegrationPolygon::getEar(std::vector<Point> points, std::vector<int>& pointList) {
    int size = (int) pointList.size();

    if(size<3){
        IntegrationTriangle t;
        return t;
    }

    if(size==3){
        IntegrationTriangle ear (pointList[0], pointList[1], pointList[2]);
        pointList.clear();
        return ear;
    }

    for(int i=0;i<size;i++){
        bool test = false;
        IntegrationTriangle t (pointList[(size+i-1)%size], pointList[i%size], pointList[(size+i+1)%size]);

        if(t.isConvex(points)){
            for(int j=0;j<size;j++){
                if(!t.isVertex(pointList[j]) && t.inside(points[pointList[j]], points)){
                    test = true;
                }
            }

            if(!test){
                pointList.erase(pointList.begin() + i);
                return t;
            }

        }

    }

    IntegrationTriangle t;
    return t;
}

