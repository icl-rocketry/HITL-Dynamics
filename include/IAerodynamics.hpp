#pragma once
#include <Eigen/Dense>
#include "State.hpp"

class IAerodynamics {
public:
    virtual ~IAerodynamics() = default;

    virtual double GetCd(const State& aerodynamicState) const = 0;
    
    virtual Eigen::Vector3d GetMomentCoefficients(const State& aerodynamicState) const = 0;
};