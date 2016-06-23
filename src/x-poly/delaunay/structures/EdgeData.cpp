#include "EdgeData.h"


EdgeData::EdgeData(int p1, int p2) {
    this->p1 = p1;
    this->p2 = p2;
    this->t1 = -1;
    this->t2 = -1;
}

void EdgeData::setTriangle(int t) {
    if(this->t1==-1){
        this->t1 = t;
    }else{
        this->t2 = t;
    }
}


