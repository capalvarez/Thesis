#ifndef THESIS_TESTLIST_H
#define THESIS_TESTLIST_H

#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/utilities/List.h>

class ListTest : public ::testing::Test{
protected:
    virtual void SetUp(){
        list = new List<Point>();

        list->push_back(Point(0,0));
        list->push_back(Point(1,0));
        list->push_back(Point(1,1));
        list->push_back(Point(0,0));
        list->push_back(Point(2,0));
    }

    List<Point>* list;
};


#endif
