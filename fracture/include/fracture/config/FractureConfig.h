#ifndef THESIS_FRACTURECONFIG_H
#define THESIS_FRACTURECONFIG_H

class FractureConfig {
private:
    double double_comparison_tolerance;
    static FractureConfig* s_instance;

    FractureConfig();
    FractureConfig(const FractureConfig& other) = delete;
    FractureConfig& operator=(const FractureConfig& copy) = delete;
public:
    void setTolerance(double t);
    double getTolerance();
    static FractureConfig* instance();
};



#endif 
