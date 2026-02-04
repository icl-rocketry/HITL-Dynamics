#pragma once

#include "State.hpp"

class ISolver
{
public:
    virtual ~ISolver() = default;

    // Performs one integration step using a precomputed derivative
    virtual State Step(
        const State& current,
        const State& derivative,
        double dt) const = 0;
};

