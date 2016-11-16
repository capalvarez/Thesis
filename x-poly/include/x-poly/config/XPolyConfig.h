#ifndef THESIS_XPOLYCONFIG_H
#define THESIS_XPOLYCONFIG_H

class XPolyConfig {
private:
    int circle_discretization_grade;
    double double_comparison_tolerance;
    int scale_for_clipper;

    static XPolyConfig* s_instance;
    XPolyConfig();
public:
    void setDiscretizationGrade(int d);
    void setTolerance(double t);
    void setScale(int s);

    int getDiscretizationGrade();
    double getTolerance();
    int getScale();

    static XPolyConfig* instance();
};


#endif 
