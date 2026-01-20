#pragma once
#include "State.hpp"

class IRocket {
public:
    virtual ~IRocket() = default;

    virtual Eigen::VectorXd GetDerivatives(const State& current) = 0;
    
    virtual double GetMass(double t) const = 0;
};