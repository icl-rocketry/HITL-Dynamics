#pragma once

#include "ISolver.hpp"

class EulerSolver : public ISolver
{
public:
    State Step(
        const State& current,
        const State& derivative,
        double dt) const override;
};
