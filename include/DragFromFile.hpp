#pragma once
#include "IAerodynamics.hpp"
#include "State.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DragFromFile : public IAerodynamics {
private:
    vector<double> mach;
    vector<double> cd; 
    double MaxMach = 0.0; 
    double MinMach = 0.0; 

    void readTable(const string& filename);
    
    double interpolateCD(double MachInput) const;

public:
    
    DragFromFile();

    explicit DragFromFile(const string& filename);

    double GetmaxMach() const;

    double GetminMach() const;

    double GetCd(const State& aerodynamicState) const override;

    double getCdFromMach(double mach) const;

    Eigen::Vector3d GetMomentCoefficients(const State& aerodynamicState) const override;
};
