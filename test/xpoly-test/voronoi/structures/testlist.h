#ifndef THESIS_TESTLIST_H
#define THESIS_TESTLIST_H

#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/utilities/List.h>

class ListTest : public ::testing::Test{
protected:
    virtual void SetUp(){
        list = new List<Point>();
        std::vector<Point> p = {Point(0,0), Point(1,0), Point(1,1), Point(0,0), Point(2,0)};

        list->push_back(p[0]);
        list->push_back(p[1]);
        list->push_back(p[2]);
        list->push_back(p[3]);
        list->push_back(p[4]);
    }

    List<Point>* list;
};


#endif
