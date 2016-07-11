#include <utilities/operations.h>
#include "DegreesOfFreedom.h"
#include "lobattoQuadrature.cpp"

DegreesOfFreedom::DegreesOfFreedom(Polygon p, int k, std::vector<Point>& points) {
    this->order = k;
    this->numberOfSides = p.numberOfSides();

    std::vector<double> quadrature_points;
    std::vector<double> weight;

    lobatto::lobatto_set(k+1,quadrature_points,weight);

    std::vector<int> polygonPoints = p.getPoints();
    this->dof.assign(polygonPoints.begin(), polygonPoints.end());

    for(int vertex_id=0; vertex_id<polygonPoints.size(); vertex_id++){
        Point p1 = points[vertex_id];
        Point p2 = points[(vertex_id+1)%polygonPoints.size()];

        for(int lobatto_id=1;lobatto_id<quadrature_points.size()-1;lobatto_id++){
            double x = p1.getX() + (p2.getX()-p1.getX())/2*(quadrature_points[lobatto_id]+1);
            double y = p1.getY() + (p2.getY()-p1.getY())/2*(quadrature_points[lobatto_id]+1);

            Point newPoint (x,y);
            points.push_back(newPoint);
            this->dof.push_back((int) points.size()-1);
        }
    }

    //TODO: For now, working up to grade 2 (only centroid as inner dof)
    if(k>1){
        points.push_back(p.getCentroid());
        this->dof.push_back((int) points.size()-1);
    }

}


int DegreesOfFreedom::numberOfDOF() {
    return (int) this->dof.size();
}

Pair<double> DegreesOfFreedom::normal(int i, std::vector<Point> points) {
    if(i<this->numberOfSides){
        Point previous;
        if(i==0){
            previous = points[numberOfSides-1];
        }else{
            previous = points[i-1];
        }

        Point next = points[(i+1)%numberOfSides];

        Pair<double> prev_vector = operations::normal(points[i], previous);
        Pair<double> next_vector = operations::normal(next, points[i]);

        return Pair<double>((prev_vector.first+next_vector.first)/2,
                            (prev_vector.second+next_vector.second)/2);

    }else{
        if(i<(this->numberOfSides*this->order - 1)){
            int edge = i/(this->order+1);
            Point p1 = points[edge];
            Point p2 = points[(edge+1)%numberOfSides];

            return operations::normal(p1,p2);
        }else{
            //TODO: Fix this patch!
            return Pair<double>(0,0);
        }
    }
}


std::vector<int> DegreesOfFreedom::getDOF() {
    return this->dof;
}






