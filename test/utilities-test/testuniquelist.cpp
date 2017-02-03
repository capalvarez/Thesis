#include <gtest/gtest.h>
#include <utilities/interfaces/Unificable.h>
#include <utilities/UniqueList.h>
#include "MyPoint.h"

TEST(UniqueListTest, CreationTest){

    UniqueList<MyPoint> list;
    MyPoint p (0,1);
    MyPoint p2 (1,1);
    MyPoint p3 (0,1);

    list.push_back(p);
    list.push_back(p2);
    list.push_back(p3);

    std::cout << list.size() << std::endl;

}