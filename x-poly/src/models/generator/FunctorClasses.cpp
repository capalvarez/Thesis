#include <x-poly/utilities/xpolyutilities.h>
#include <cmath>
#include <random>
#include <x-poly/models/generator/Functor.h>
#include <time.h>
#include <ctime>

class Constant : public Functor {
public:
    Constant() {}
    inline double apply(double x){ return x;}
};

class Uniform : public Functor {
private:
    double delta;
public:
    Uniform(double delta){ this->delta = delta;}
    inline double apply(double x){ return x*delta;}
};

class Sine : public Functor {
private:
    double amplitude;
    double frecuency;
    double phase;
public:
    Sine(double a, double f, double p){
        this->amplitude = a;
        this->frecuency = f;
        this->phase = p;
    }

    inline double apply(double x){
        return amplitude*std::sin(frecuency*utilities::radian(x) + utilities::radian(phase));
    };
};

class Cosine : public Functor {
private:
    double amplitude;
    double frecuency;
    double phase;
public:
    Cosine(double a, double f, double p){
        this->amplitude = a;
        this->frecuency = f;
        this->phase = p;
    }

    inline double apply(double x){
        return amplitude*std::cos(frecuency*utilities::radian(x) + utilities::radian(phase));
    };
};

class Random_Integer : public Functor {
private:
    double min;
    double max;
    std::random_device rd;
    std::mt19937* rng;
    std::uniform_int_distribution<int>* uni;
public:
    Random_Integer(double min, double max){
        this->min = min;
        this->max = max;
        this->rng = new std::mt19937(rd());
        this->uni = new std::uniform_int_distribution<int>(min,max);
    }

    ~Random_Integer(){
        delete(rng);
        delete(uni);
    }

    inline double apply(double x){return (*uni)(*this->rng);}
};

class Random_Double : public Functor {
public:
    double min;
    double max;
    std::random_device r;
    std::default_random_engine rd;
    std::mt19937 rng;
    std::uniform_real_distribution<double> uni;

    Random_Double(double min, double max){
        this->min = min;
        this->max = max;
        this->rd = std::default_random_engine((std::time(nullptr)));
        this->rng = std::mt19937(rd());
        this->uni = std::uniform_real_distribution<double>(min,max);
    }

    ~Random_Double(){}

    inline double apply(double x){return (uni)(this->rng);}
};


