#include <cmath>
#include <iostream>
#include "IsaEnvironment.hpp"

int main() {
    IsaEnvironment env;
    bool pass = true;

    auto CheckNear = [&](const char* name, double value, double expected, double tol) {
        const double err = std::abs(value - expected);
        std::cout << name << ": " << value << " (expected ~" << expected << ")\n";
        if (err > tol) {
            pass = false;
            std::cout << "  FAIL (error " << err << " > tol " << tol << ")\n";
        }
    };

    // Sea level checks
    CheckNear("P(0 m) [Pa]", env.GetPressure(0.0), 101325.0, 500.0);
    CheckNear("rho(0 m) [kg/m^3]", env.GetDensity(0.0), 1.225, 0.02);
    CheckNear("a(0 m) [m/s]", env.GetSpeedOfSound(0.0), 340.3, 1.0);

    // 11 km checks
    CheckNear("P(11000 m) [Pa]", env.GetPressure(11000.0), 22632.0, 500.0);
    CheckNear("rho(11000 m) [kg/m^3]", env.GetDensity(11000.0), 0.364, 0.02);
    CheckNear("a(11000 m) [m/s]", env.GetSpeedOfSound(11000.0), 295.1, 1.0);

    // 20 km checks
    CheckNear("P(20000 m) [Pa]", env.GetPressure(20000.0), 5475.0, 200.0);
    CheckNear("rho(20000 m) [kg/m^3]", env.GetDensity(20000.0), 0.088, 0.01);
    CheckNear("a(20000 m) [m/s]", env.GetSpeedOfSound(20000.0), 295.1, 1.0);

    // Gravity direction and magnitude sanity check
    const Eigen::Vector3d pos(0.0, 0.0, 6371000.0);
    const Eigen::Vector3d g = env.GetGravityVector(pos);
    CheckNear("|g| at Earth radius [m/s^2]", g.norm(), 9.82, 0.1);
    if (g.z() >= 0.0) {
        pass = false;
        std::cout << "Gravity direction FAIL: z should be negative.\n";
    }

    // Wind default check
    const Eigen::Vector3d w = env.GetWind(5000.0);
    if (w.norm() != 0.0) {
        pass = false;
        std::cout << "Wind FAIL: expected zero vector.\n";
    }

    std::cout << (pass ? "\nALL TESTS PASSED\n" : "\nTESTS FAILED\n");
    return pass ? 0 : 1;
}
