#pragma once
#include "IRocket.hpp"
#include "State.hpp"

class ISolver {
public:
    virtual ~ISolver() = default;

    virtual State Step(IRocket& rocket, const State& current, double dt) = 0;
};