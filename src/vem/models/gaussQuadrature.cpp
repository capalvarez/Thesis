#include <x-poly/models/basic/Point.h>
#include <vector>

namespace gauss{
    void gaussQuadrature(int order, std::vector<Point>& points, std::vector<double>& weight){
        if (order == 1){
            points.push_back(Point(0.33333333333333,0.33333333333333));

            weight.push_back(1.00000000000000);
        }else if(order == 2){
            points.push_back(Point(0.16666666666667,0.16666666666667));
            points.push_back(Point(0.16666666666667,0.66666666666667));
            points.push_back(Point(0.66666666666667,0.16666666666667));

            weight.push_back(0.33333333333333);
            weight.push_back(0.33333333333333);
            weight.push_back(0.33333333333333);
        }else if(order == 3){
            points.push_back(Point(0.33333333333333,0.33333333333333));
            points.push_back(Point(0.20000000000000,0.20000000000000));
            points.push_back(Point(0.20000000000000,0.60000000000000));
            points.push_back(Point(0.60000000000000,0.20000000000000));

            weight.push_back(-0.56250000000000);
            weight.push_back(0.52083333333333);
            weight.push_back(0.52083333333333);
            weight.push_back(0.52083333333333);
        }else if(order == 4){
            points.push_back(Point(0.44594849091597,0.44594849091597));
            points.push_back(Point(0.44594849091597,0.10810301816807));
            points.push_back(Point(0.10810301816807,0.44594849091597));
            points.push_back(Point(0.09157621350977,0.09157621350977));
            points.push_back(Point(0.09157621350977,0.81684757298046));
            points.push_back(Point(0.81684757298046,0.09157621350977));

            weight.push_back(0.22338158967801);
            weight.push_back(0.22338158967801);
            weight.push_back(0.22338158967801);
            weight.push_back(0.10995174365532);
            weight.push_back(0.10995174365532);
            weight.push_back(0.10995174365532);
        }else if(order == 5){
            points.push_back(Point(0.33333333333333,0.33333333333333));
            points.push_back(Point(0.47014206410511,0.47014206410511));
            points.push_back(Point(0.47014206410511,0.05971587178977));
            points.push_back(Point(0.05971587178977,0.47014206410511));
            points.push_back(Point(0.10128650732346,0.10128650732346));
            points.push_back(Point(0.10128650732346,0.79742698535309));
            points.push_back(Point(0.79742698535309,0.10128650732346));

            weight.push_back(0.22500000000000);
            weight.push_back(0.13239415278851);
            weight.push_back(0.13239415278851);
            weight.push_back(0.13239415278851);
            weight.push_back(0.12593918054483);
            weight.push_back(0.12593918054483);
            weight.push_back(0.12593918054483);
        }else if(order == 6){
            points.push_back(Point(0.24928674517091,0.24928674517091));
            points.push_back(Point(0.24928674517091,0.50142650965818));
            points.push_back(Point(0.50142650965818,0.24928674517091));
            points.push_back(Point(0.06308901449150,0.06308901449150));
            points.push_back(Point(0.06308901449150,0.87382197101700));
            points.push_back(Point(0.87382197101700,0.06308901449150));
            points.push_back(Point(0.31035245103378,0.63650249912140));
            points.push_back(Point(0.63650249912140,0.05314504984482));
            points.push_back(Point(0.05314504984482,0.31035245103378));
            points.push_back(Point(0.63650249912140,0.31035245103378));
            points.push_back(Point(0.31035245103378,0.05314504984482));
            points.push_back(Point(0.05314504984482,0.63650249912140));

            weight.push_back(0.11678627572638);
            weight.push_back(0.11678627572638);
            weight.push_back(0.11678627572638);
            weight.push_back(0.05084490637021);
            weight.push_back(0.05084490637021);
            weight.push_back(0.05084490637021);
            weight.push_back(0.08285107561837);
            weight.push_back(0.08285107561837);
            weight.push_back(0.08285107561837);
            weight.push_back(0.08285107561837);
            weight.push_back(0.08285107561837);
            weight.push_back(0.08285107561837);
        }else if(order == 7){
            points.push_back(Point(0.33333333333333,0.33333333333333));
            points.push_back(Point(0.26034596607904,0.26034596607904));
            points.push_back(Point(0.26034596607904,0.47930806784192));
            points.push_back(Point(0.47930806784192,0.26034596607904));
            points.push_back(Point(0.06513010290222,0.06513010290222));
            points.push_back(Point(0.06513010290222,0.86973979419557));
            points.push_back(Point(0.86973979419557,0.06513010290222));
            points.push_back(Point(0.31286549600487,0.63844418856981));
            points.push_back(Point(0.63844418856981,0.04869031542532));
            points.push_back(Point(0.04869031542532,0.31286549600487));
            points.push_back(Point(0.63844418856981,0.31286549600487));
            points.push_back(Point(0.31286549600487,0.04869031542532));
            points.push_back(Point(0.04869031542532,0.63844418856981));

            weight.push_back(-0.14957004446768);
            weight.push_back(0.17561525743321);
            weight.push_back(0.17561525743321);
            weight.push_back(0.17561525743321);
            weight.push_back(0.05334723560884);
            weight.push_back(0.05334723560884);
            weight.push_back(0.05334723560884);
            weight.push_back(0.07711376089026);
            weight.push_back(0.07711376089026);
            weight.push_back(0.07711376089026);
            weight.push_back(0.07711376089026);
            weight.push_back(0.07711376089026);
            weight.push_back(0.07711376089026);
        }else{
            points.push_back(Point(0.33333333333333,0.33333333333333));
            points.push_back(Point(0.45929258829272,0.45929258829272));
            points.push_back(Point(0.45929258829272,0.08141482341455));
            points.push_back(Point(0.08141482341455,0.45929258829272));
            points.push_back(Point(0.17056930775176,0.17056930775176));
            points.push_back(Point(0.17056930775176,0.65886138449648));
            points.push_back(Point(0.65886138449648,0.17056930775176));
            points.push_back(Point(0.05054722831703,0.05054722831703));
            points.push_back(Point(0.05054722831703,0.89890554336594));
            points.push_back(Point(0.89890554336594,0.05054722831703));
            points.push_back(Point(0.26311282963464,0.72849239295540));
            points.push_back(Point(0.72849239295540,0.00839477740996));
            points.push_back(Point(0.00839477740996,0.26311282963464));
            points.push_back(Point(0.72849239295540,0.26311282963464));
            points.push_back(Point(0.26311282963464,0.00839477740996));
            points.push_back(Point(0.00839477740996,0.72849239295540));

            weight.push_back(0.14431560767779);
            weight.push_back(0.09509163426728);
            weight.push_back(0.09509163426728);
            weight.push_back(0.09509163426728);
            weight.push_back(0.10321737053472);
            weight.push_back(0.10321737053472);
            weight.push_back(0.10321737053472);
            weight.push_back(0.03245849762320);
            weight.push_back(0.03245849762320);
            weight.push_back(0.03245849762320);
            weight.push_back(0.02723031417443);
            weight.push_back(0.02723031417443);
            weight.push_back(0.02723031417443);
            weight.push_back(0.02723031417443);
            weight.push_back(0.02723031417443);
            weight.push_back(0.02723031417443);
        }
    }
}

