#pragma once
#include "IRocket.hpp"
#include "SimplePropulsion.hpp"
#include "IsaEnvironment.hpp"
#include "DragFromFile.hpp"
#include "State.hpp"
#include <cmath>

class OneDRocket : public IRocket {
private:
    double Machinput = 0.0;
    double totalpropmass;
    double totalmass;
    double drymass;
    double area;
    SimplePropulsion& engine;
    DragFromFile& aero;
    IsaEnvironment& env;  
    State RocketState;
    State dState;
    State AerodynamicState;

public:
    OneDRocket(double drymass_input, double totalpropmass_input, double area_input, SimplePropulsion& engine_input, DragFromFile& aero_input, IsaEnvironment& env_input);

    Eigen::VectorXd GetDerivatives(const State& current) override;

    State GetnewRocketState(const State& current, const State& derivative);

    double GetMass(double) const override;
};