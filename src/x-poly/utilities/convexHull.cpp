#include <bits/stl_bvector.h>
#include <geometry/Point.h>
#include <geometry/Polygon.h>
#include <algorithm>

namespace convex {
   struct PointComparator{
       bool operator()(Point p1, Point p2){
           if(p1.getX()== p2.getX()){
               return p1.getY() < p2.getY();
           }

           return p1.getX() < p2.getX();
       }
   } comparator;

    Polygon convexHull(std::vector<Point> points){
        std::vector<Point> upper;
        std::vector<Point> lower;

        std::sort(points.begin(), points.end(), comparator);
        for(int i=0;i<points.size();i++){

            while(upper.size()>1 && orientation(upper[points.size()-1], upper[points.size()-2],points[i])<=0){
                upper.pop_back();
            }

            while(lower.size()>1 && orientation(lower[points.size()-1], lower[points.size()-2],points[i])<=0){
                lower.pop_back();
            }

            upper.push_back(points[i]);
            lower.push_back(points[i]);
        }

        return
    }

    double rotatingCalipers(){

    }

    double orientation(Point p, Point q, Point r){
        return ((q-p)^(r-p)).getPoint()->getZ();
    }

    def hulls(Points):
    '''Graham scan to find upper and lower convex hulls of a set of 2d points.'''
        U = []
        L = []
            Points.sort()
            for p in Points:
            while len(U) > 1 and orientation(U[-2],U[-1],p) <= 0: U.pop()
            while len(L) > 1 and orientation(L[-2],L[-1],p) >= 0: L.pop()
            U.append(p)
            L.append(p)
            return U,L
}

