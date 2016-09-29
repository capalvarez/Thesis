#ifndef THESIS_LIST_H
#define THESIS_LIST_H

#include <vector>
#include <x-poly/models/basic/Point.h>
#include <algorithm>
#include <x-poly/models/polygon/Polygon.h>

template <typename T>
class List {
private:
    std::vector<T> list;
public:
    List();
    int push_back(T item);
    int size();
    std::vector<int> push_list(std::vector<T> list);

    std::vector<T> getList() const;
    T get(int i);
    bool operator==(const List<T>& other);
    bool contains(T elem);
};


#endif