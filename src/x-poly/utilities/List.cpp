#include <algorithm>
#include "List.h"

template <typename T>
List<T>::List() {}

template <typename T>
int List<T>::push_back(T item) {
    int index = std::find(list.begin(), list.end(), item);

    if(index!=list.end()){
        return index;
    }

    list.push_back(item);

    return (int) list.size()-1;
}

template <typename T>
int List<T>::size() {
    return (int) list.size();
}

template <typename T>
std::vector<Point> List::getList() {
    return this->list;
}



