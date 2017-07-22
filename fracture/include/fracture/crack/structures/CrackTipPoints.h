#ifndef THESIS_CRACKTIPPOINTS_H
#define THESIS_CRACKTIPPOINTS_H

struct CrackTipPoints {
    int center;

    int b;
    int c;
    int d;
    int e;

    CrackTipPoints(int Center, int bP, int cP, int dP, int eP){
        center = Center;

        b = bP;
        c = cP;
        d = dP;
        e = eP;
    };

    CrackTipPoints(){};
};

#endif