#ifndef THESIS_VEAMYLIST_H
#define THESIS_VEAMYLIST_H

#include <vector>
#include <veamy/models/dof/DOF.h>

template <class T>
class VeamyList {
private:
    std::vector<T> list;
public:
    VeamyList();
    int push_back(T item);
    int size();
    std::vector<int> push_list(std::vector<T> list);

    std::vector<T> getList() const;
    T get(int i);
    bool operator==(const VeamyList<T>& other);
    bool contains(T elem);
};


#endif
