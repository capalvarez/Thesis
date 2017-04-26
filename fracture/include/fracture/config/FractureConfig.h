#ifndef THESIS_FRACTURECONFIG_H
#define THESIS_FRACTURECONFIG_H

class FractureConfig {
private:
    double double_comparison_tolerance;
    double crack_growth_speed;
    double crack_size_ratio;
    double rosette_angle;
    int max_iterations;

    static FractureConfig* s_instance;

    FractureConfig();
    FractureConfig(const FractureConfig& other) = delete;
    FractureConfig& operator=(const FractureConfig& copy) = delete;
public:
    void setTolerance(double t);
    void setGrowthSpeed(double s);
    void setCrackRatio(double r);
    void setRosetteAngle(double a);
    void setMaxIterations(int i);

    double getTolerance();
    double getSpeed();
    double getRatio();
    double getRosetteAngle();
    int getMaxIterations();

    static FractureConfig* instance();
};



#endif 
