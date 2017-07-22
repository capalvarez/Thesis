#ifndef THESIS_DEQUE_H
#define THESIS_DEQUE_H

#include <deque>

template <class T>
class Deque{
private:
    std::vector<T> firstToLast;
    std::vector<T> lastToFirst;
public:
    Deque();
    void push_front(T& item);
    void push_back(T& item);
    void insert(std::vector<T> elems);
    void insert_front(std::vector<T> elems);
    T& operator[](int i);

    T& first();
    T& second();
    T& secondToLast();
    T& last();

    std::vector<T> getFirstToLast();
    std::vector<T> getLastToFirst();

    int size();
    void clear();
};

template <class T>
Deque<T>::Deque() {}

template <class T>
void Deque<T>::push_front(T &item) {
    this->lastToFirst.push_back(item);

    if(this->firstToLast.size()==0){
        this->firstToLast.push_back(item);
    } else{
        this->firstToLast.insert(this->firstToLast.begin(), item);
    }
}

template <class T>
void Deque<T>::push_back(T &item) {
    this->firstToLast.push_back(item);

    if(this->lastToFirst.size()==0){
        this->lastToFirst.push_back(item);
    }else{
        this->lastToFirst.insert(this->lastToFirst.begin(), item);
    }
}

template <class T>
void Deque<T>::insert(std::vector<T> elems) {
    for(int i = 0; i<elems.size(); i++){
        this->push_back(elems[i]);
    }
}

template <class T>
void Deque<T>::insert_front(std::vector<T> elems) {
    for(int i = 0; i<elems.size(); i++){
        this->push_front(elems[i]);
    }
}

template <class T>
T &Deque<T>::operator[](int i) {
    return this->firstToLast[i];
}

template <class T>
T& Deque<T>::first() {
    return this->firstToLast.front();
}

template <class T>
T& Deque<T>::second() {
    if(this->firstToLast.size()==1){
        return this->firstToLast[0];
    }

    return this->firstToLast[1];
}

template <class T>
T& Deque<T>::secondToLast() {
    if(this->firstToLast.size()==1){
        return this->firstToLast.back();
    }

    return this->firstToLast[this->firstToLast.size()-2];
}

template <class T>
T& Deque<T>::last() {
    return this->firstToLast.back();
}

template <class T>
int Deque<T>::size() {
    return this->firstToLast.size();
}

template <class T>
void Deque<T>::clear() {
    this->firstToLast.clear();
    this->lastToFirst.clear();
}

template <class T>
std::vector<T> Deque<T>::getFirstToLast() {
    return this->firstToLast;
}

template <class T>
std::vector<T> Deque<T>::getLastToFirst() {
    return this->lastToFirst;
}

#endif