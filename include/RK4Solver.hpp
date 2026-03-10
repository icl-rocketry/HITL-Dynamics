#pragma once

#include "ISolver.hpp"

class RK4Solver : public ISolver
{
public:
    void Step(
        IRocket& rocket,
        State& state,
        double dt) const override;
};