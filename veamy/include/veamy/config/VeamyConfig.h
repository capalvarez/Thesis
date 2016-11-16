#ifndef THESIS_VEAMYCONFIG_H
#define THESIS_VEAMYCONFIG_H

class VeamyConfig{
private:
    double double_comparison_tolerance;

    static VeamyConfig* s_instance;
    VeamyConfig();
public:
    void setTolerance(double t);

    double getTolerance();

    static VeamyConfig* instance();
};

#endif 
