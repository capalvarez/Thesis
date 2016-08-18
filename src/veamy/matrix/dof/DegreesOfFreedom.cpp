#include <utilities/operations.h>
#include "DegreesOfFreedom.h"

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

std::vector<int> DegreesOfFreedom::getDOF() {
    return this->dof;
}

std::vector<int> DegreesOfFreedom::getNeighbours(int dof) {
    std::vector<int> neighbours;

    if(dof<this->numberOfSides){
        neighbours.push_back((numberOfSides + dof-1)%numberOfSides);

        for(int i=0;i<this->order-1;i++){
            neighbours.push_back(numberOfSides + (numberOfSides + dof-1)%numberOfSides*(order-1) + i);
        }

        neighbours.push_back(dof);

        for(int i=0;i<this->order-1;i++){
            neighbours.push_back(numberOfSides + (numberOfSides + dof)%numberOfSides*(order-1) + i);
        }

        neighbours.push_back((dof + 1)%numberOfSides);
    } else {

    }







}







