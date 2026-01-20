#pragma once
#include <Eigen/Dense>

class IAerodynamics {
public:
    virtual ~IAerodynamics() = default;

    virtual double GetCd(double mach, double alpha, double beta) const = 0;
    virtual double GetCl(double mach, double alpha, double beta) const = 0;
    
    virtual Eigen::Vector3d GetMomentCoefficients(double mach, double alpha, double beta) const = 0;
};