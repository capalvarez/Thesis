#include <algorithm>
#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Segment.h>
#include <veamy/models/dof/OuterDOF.h>
#include "List.h"

template <typename T>
List<T>::List() {}

template <typename T>
int List<T>::push_back(T item) {
    typename std::vector<T>::iterator index;
    index = std::find(list.begin(), list.end(), item);

    if(index!=list.end()){
        return (int) std::distance(list.begin(),index);
    }

    list.push_back(item);

    return (int) list.size()-1;
}

template <typename T>
int List<T>::size() {
    return (int) list.size();
}

template <typename T>
std::vector<T> List<T>::getList() const{
    return this->list;
}

template <typename T>
bool List<T>::operator==(const List<T> &other) {
    return this->list==other.getList();
}

template <typename T>
T List<T>::get(int i) {
    return list[i];
}

template <typename T>
std::vector<int> List<T>::push_list(std::vector<T> list) {
    std::vector<int> index;

    for(int i=0;i<list.size();i++){
        index.push_back(this->push_back(list[i]));
    }

    return index;
}

template <typename T>
bool List<T>::contains(T elem) {
    return std::find(list.begin(), list.end(), elem) != list.end();;
}


template class List<Point>;
template class List<Segment>;
template class List<Polygon>;
template class List<int>;
template class List<DOF*>;




