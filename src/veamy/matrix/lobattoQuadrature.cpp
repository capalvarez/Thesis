#include "lobattoQuadrature.h"

/*
 * This file contains the Lobatto quadrature routine adapted from QUADRULE.
 *
 */
namespace lobatto {
    void lobatto_set(int order, std::vector<double>& xtab, std::vector<double>& weight) {
        if (order == 1) {
            xtab.push_back(-1.0);
            weight.push_back(2.0);
        }
        else if (order == 2) {
            xtab.push_back(-1.0E+00);
            xtab.push_back(1.0E+00);

            weight.push_back(1.0E+00);
            weight.push_back(1.0E+00);
        }
        else if (order == 3) {
            xtab.push_back(-1.0E+00);
            xtab.push_back(0.0E+00);
            xtab.push_back(1.0E+00);

            weight.push_back(1.0 / 3.0E+00);
            weight.push_back(4.0 / 3.0E+00);
            weight.push_back(1.0 / 3.0E+00);
        }
        return;
    }
}
