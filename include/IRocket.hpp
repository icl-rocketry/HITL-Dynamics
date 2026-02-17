#pragma once
#include "State.hpp"
#include "RocketModel.hpp"

class IRocket : public RocketModel {
public:
    virtual ~IRocket() = default;

    virtual Eigen::VectorXd GetDerivatives(const State& current) = 0;
};