#include "EulerSolver.hpp"

void EulerSolver::Step(
    IRocket& rocket,
    State& state,
    double dt) const
{
    Eigen::VectorXd dx = rocket.GetDerivatives(state);

    State derivative(state.size());
    derivative.data = dx;

    state = state + derivative * dt;
}