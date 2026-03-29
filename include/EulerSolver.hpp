#pragma once

#include "ISolver.hpp"

class EulerSolver : public ISolver
{
public:
    void Step(
        IRocket& rocket,
        State& state,
        double dt) const override;
};