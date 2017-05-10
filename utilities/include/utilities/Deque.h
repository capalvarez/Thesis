#ifndef THESIS_DEQUE_H
#define THESIS_DEQUE_H

#include <deque>

template <class T>
class Deque{
private:
    std::deque<T> deque;
public:
    Deque();
    void push_front(T& item);
    void push_back(T& item);
    void insert(std::vector<T> elems);
    T& operator[](int i);

    T& first();
    T& second();
    T& secondToLast();
    T& last();

    int size();
    void clear();
};

template <class T>
Deque<T>::Deque() {}

template <class T>
void Deque<T>::push_front(T &item) {
    this->deque.push_front(item);
}

template <class T>
void Deque<T>::push_back(T &item) {
    this->deque.push_back(item);
}

template <class T>
void Deque<T>::insert(std::vector<T> elems) {
    this->deque.insert(deque.begin(), elems.begin(), elems.end());
}

template <class T>
T &Deque<T>::operator[](int i) {
    return this->deque[i];
}

template <class T>
T& Deque<T>::first() {
    return this->deque.front();
}

template <class T>
T& Deque<T>::second() {
    if(this->deque.size()==1){
        return this->deque[0];
    }

    return this->deque[1];
}

template <class T>
T& Deque<T>::secondToLast() {
    if(this->deque.size()==1){
        return this->deque.back();
    }

    return this->deque[this->deque.size()-2];
}

template <class T>
T& Deque<T>::last() {
    return this->deque.back();
}

template <class T>
int Deque<T>::size() {
    return this->deque.size();
}

template <class T>
void Deque<T>::clear() {
    this->deque.clear();
}

#endif