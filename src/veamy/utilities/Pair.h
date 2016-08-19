#ifndef THESIS_PAIR_H
#define THESIS_PAIR_H

template <typename T>
class Pair {
public:
    T first;
    T second;

    Pair(T first, T second);
    Pair(const Pair& other);
    Pair();
    bool operator==(const Pair& other) const;
    T dot(Pair other);
    Pair<T> average(Pair<T> other);
};


#endif //THESIS_PAIR_H
