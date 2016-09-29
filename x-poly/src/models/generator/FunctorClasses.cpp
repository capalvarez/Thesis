#include <x-poly/utilities/utilities.h>
#include <cmath>
#include <random>
#include <x-poly/models/generator/Functor.h>

class Constant : public Functor {
public:
    Constant() {}
    inline double operator()(double x){ return x;}
};

class Uniform : public Functor {
private:
    double delta;
public:
    Uniform(double delta){ this->delta = delta;}
    inline double operator()(double x){ return x*delta;}
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

    inline double operator()(double x){
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

    inline double operator()(double x){
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

    inline double operator()(double x){return (*uni)(*this->rng);}
};

class Random_Double : public Functor {
private:
    double min;
    double max;
    std::random_device rd;
    std::mt19937* rng;
    std::uniform_real_distribution<double>* uni;
public:
    Random_Double(double min, double max){
        this->min = min;
        this->max = max;
        this->rng = new std::mt19937(rd());
        this->uni = new std::uniform_real_distribution<double>(min,max);
    }

    ~Random_Double(){
        delete(rng);
        delete(uni);
    }

    inline double operator()(double x){return (*uni)(*this->rng);}
};


