#include "RK4Solver.hpp"

void RK4Solver::Step(
    IRocket& rocket,
    State& state,
    double dt) const
{
    const State x = state;

    // k1
    State k1(x.size());
    k1.data = rocket.GetDerivatives(x);

    // k2
    State x2 = x + k1 * (dt * 0.5);
    State k2(x.size());
    k2.data = rocket.GetDerivatives(x2);

    // k3
    State x3 = x + k2 * (dt * 0.5);
    State k3(x.size());
    k3.data = rocket.GetDerivatives(x3);

    // k4
    State x4 = x + k3 * dt;
    State k4(x.size());
    k4.data = rocket.GetDerivatives(x4);

    // Final RK4 update
    state = x + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (dt / 6.0);
}
