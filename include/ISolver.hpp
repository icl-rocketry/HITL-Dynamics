#pragma once

#include "IRocket.hpp"
#include "State.hpp"

class ISolver
{
public:
    virtual ~ISolver() = default;

    virtual void Step(
        IRocket& rocket,
        State& state,
        double dt) const = 0;
};

