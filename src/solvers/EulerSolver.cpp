#include "EulerSolver.hpp"

State EulerSolver::Step(
    const State& current,
    const State& derivative,
    double dt) const
{
    return current + derivative * dt;
}
