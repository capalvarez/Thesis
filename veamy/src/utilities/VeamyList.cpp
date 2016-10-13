#include <algorithm>
#include <veamy/utilities/VeamyList.h>


template <typename T>
VeamyList<T>::VeamyList() {}

template <typename T>
int VeamyList<T>::push_back(T item) {
    typename std::vector<T>::iterator index;
    index = std::find(list.begin(), list.end(), item);

    if(index!=list.end()){
        return (int) std::distance(list.begin(),index);
    }

    list.push_back(item);

    return (int) list.size()-1;
}

template <typename T>
int VeamyList<T>::size() {
    return (int) list.size();
}

template <typename T>
std::vector<T> VeamyList<T>::getList() const{
    return this->list;
}

template <typename T>
bool VeamyList<T>::operator==(const VeamyList<T> &other) {
    return this->list==other.getList();
}

template <typename T>
T VeamyList<T>::get(int i) {
    return list[i];
}

template <typename T>
std::vector<int> VeamyList<T>::push_list(std::vector<T> list) {
    std::vector<int> index;

    for(int i=0;i<list.size();i++){
        index.push_back(this->push_back(list[i]));
    }

    return index;
}

template <typename T>
bool VeamyList<T>::contains(T elem) {
    return std::find(list.begin(), list.end(), elem) != list.end();;
}

template class VeamyList<DOF>;
template class VeamyList<Segment<int>>;
template class VeamyList<Segment<Point>>;








