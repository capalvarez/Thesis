#include <x-poly/models/basic/Point.h>
#include <vector>
#include <include/x-poly/config/XPolyConfig.h>
#include <x-poly/utilities/xpolyutilities.h>

namespace geometry_functions{
    double area2(Point p1, Point p2, Point p3){
        Point v1 = p2 - p1;
        Point v2 = p3 - p1;

        return xpoly_utilities::crossProduct(v1,v2);
    }

    bool collinear(Point p1, Point p2, Point p3){
        XPolyConfig* config = XPolyConfig::instance();

        return std::abs(area2(p1,p2,p3))<config->getTolerance();
    }

    double triangleArea(Point p1, Point p2, Point origin){
        return area2(p1,p2,origin)/2.0;
    }

    double area(std::vector<Point> points, std::vector<int> index){
        double area = 0.0;
        int n = (int) index.size();

        for(int i=0; i<n; i++) {
            area += triangleArea(points[index[i%n]],points[index[(i+1)%n]],
                                 points[index[0]]);
        }

        return area;
    }

    double area(std::vector<Point> points){
        double area = 0.0;
        int n = (int) points.size();

        for(int i=0; i<n; i++) {
            area += triangleArea(points[i%n], points[(i+1)%n], points[0]);
        }

        return area;
    }

}
