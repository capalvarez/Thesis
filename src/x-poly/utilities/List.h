#ifndef THESIS_LIST_H
#define THESIS_LIST_H

#include <vector>
#include <x-poly/models/basic/Point.h>

template <typename T>
class List {
private:
    std::vector<T> list;
public:
    List();
    int push_back(T item);
    int size();

    std::vector<Point> getList();
};


#endif