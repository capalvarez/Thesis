#include "lobattoQuadrature.h"

/*
 * This file contains the Lobatto quadrature routine adapted from QUADRULE.
 *
 */
namespace lobatto {
    void lobatto_set(int order, std::vector<double>& xtab, std::vector<double>& weight) {
        if (order == 1) {
            xtab.push_back(0.0);
            weight.push_back(1.0);
        }
        else if (order == 2) {
            xtab.push_back(0.0E+00);
            xtab.push_back(1.0E+00);

            weight.push_back(1.0 / 2.0E+00);
            weight.push_back(1.0 / 2.0E+00);
        }
        else if (order == 3) {
            xtab.push_back(0.0E+00);
            xtab.push_back(0.5E+00);
            xtab.push_back(1.0E+00);

            weight.push_back(1.0 / 6.0E+00);
            weight.push_back(4.0 / 6.0E+00);
            weight.push_back(1.0 / 6.0E+00);
        }else if (order == 4) {
            xtab.push_back(0.0E+00);
            xtab.push_back(0.276393202+00);
            xtab.push_back(0.723606798E+00);
            xtab.push_back(1.0E+00);

            weight.push_back(1.0E+00 / 12.0E+00);
            weight.push_back(5.0E+00 / 12.0E+00);
            weight.push_back(5.0E+00 / 12.0E+00);
            weight.push_back(1.0E+00 / 12.0E+00);
        }
        return;
    }
}
