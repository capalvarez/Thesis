#include "Pair.h"

template <typename T>
Pair<T>::Pair(T first, T second) {
    this->first = first;
    this->second = second;
}

template <typename T>
Pair<T>::Pair(const Pair &other) {
    this->first = other.first;
    this->second = other.second;
}

template <typename T>
Pair<T>::Pair() {}

template <typename T>
bool Pair<T>::operator==(const Pair &other) const{
    return this->first == other.first && this->second == other.second;
}

template <typename T>
T Pair<T>::dot(Pair other) {
    return this->first*other.first + this->second*other.second;
}

template <typename T>
Pair<T> Pair<T>::average(Pair<T> other) {
    return Pair<T>((this->first+other.first)/2, (this->second+other.second)/2);
}

template class Pair<int>;
template class Pair<double>;

