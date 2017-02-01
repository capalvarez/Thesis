#include <utilities/interfaces/Unificable.h>

class MyPoint : public Unificable{
private:
    int x;
    int y;
public:
    MyPoint(int x, int y){
        this->x = x;
        this->y = y;
    }

    bool operator==(MyPoint const& rhs) const;
};