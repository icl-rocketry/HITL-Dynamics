#pragma once
#include "State.hpp"

class ISolver {
public:
    virtual ~ISolver() = default;

    virtual State Step(const State& current, double dt) = 0;
};