#ifndef THESIS_XPOLYCONFIG_H
#define THESIS_XPOLYCONFIG_H

class Config {
private:
    int circle_discretization_grade;
    double double_comparison_tolerance;
    int scale_for_clipper;

    static Config* s_instance;
    Config();
public:
    void setDiscretizationGrade(int d);
    void setTolerance(double t);
    void setScale(int s);

    int getDiscretizationGrade();
    double getTolerance();
    int getScale();

    static Config* instance();
};


#endif 
