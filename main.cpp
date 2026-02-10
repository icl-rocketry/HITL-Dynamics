#include "Rocket.hpp"

#include <iostream>
#include <iomanip>

int main() {
    Rocket rocket;

    const double dt = 1;   // time step (s)
    const double simTime = 20.0;

    for (double t = 0.0; t <= simTime; t += dt) {
        

        std::cout
            << std::fixed << std::setprecision(3)
            << t << "  "
            << rocket.GetAltitude() << "  "
            << rocket.GetVelocity() << "  "
            << rocket.GetAcceleration() << "  "
            << rocket.GetFuelMass()
            << '\n';
        rocket.TimeStep(dt);
    }

    return 0;
}
