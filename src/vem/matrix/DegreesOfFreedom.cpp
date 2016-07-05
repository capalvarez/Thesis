#include "DegreesOfFreedom.h"
#include "lobattoQuadrature.cpp"

DegreesOfFreedom::DegreesOfFreedom(Polygon p, int k, std::vector<Point>& points) {
    this->order = k;

    std::vector<double> quadrature_points;
    std::vector<double> weight;

    lobatto::lobatto_set(k+1,quadrature_points,weight);

    std::vector<int> polygonPoints = p.getPoints();
    this->vertex.assign(polygonPoints.begin(), polygonPoints.end());

    for(int vertex_id=0; vertex_id<polygonPoints.size(); vertex_id++){
        Point p1 = points[vertex_id];
        Point p2 = points[(vertex_id+1)%polygonPoints.size()];

        for(int lobatto_id=1;lobatto_id<quadrature_points.size()-1;lobatto_id++){
            double x = p1.getX() + (p2.getX()-p1.getX())/2*(quadrature_points[lobatto_id]+1);
            double y = p1.getY() + (p2.getY()-p1.getY())/2*(quadrature_points[lobatto_id]+1);

            Point newPoint (x,y);
            points.push_back(newPoint);
            this->edges.push_back((int) points.size()-1);
        }
    }
}


int DegreesOfFreedom::numberOfDOF() {
    return (int) this->vertex.size() + (int) this->edges.size() + (int) this->inner.size();
}

std::pair<double, double> DegreesOfFreedom::normal(int i, std::vector<Point> points) {
    if(i<this->vertex.size()){
        Point previous;
        if(i==0){
            previous = points[vertex.size()-1];
        }else{
            previous = points[i-1];
        }

        Point next = points[(i+1)%vertex.size()];

        return std::pair<double,double>(std::make_pair((next.getX()-previous.getX())/2, (next.getY()-previous.getY())/2));
    }else{
        if(i<(this->vertex.size()+this->edges.size())){
            int edge = i/(this->order+1);
            Point p1 = points[edge];
            Point p2 = points[(edge+1)%vertex.size()];

            return std::pair<double, double>(std::make_pair(-(p2.getY()-p1.getY()), p2.getX()-p1.getX()));
        }else{
            //TODO: Fix this patch!
            return std::pair<double,double>(std::make_pair(0,0));
        }
    }


}





