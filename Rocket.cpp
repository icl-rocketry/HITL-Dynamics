#include "Rocket.hpp"

#include <cmath>

// ---------------- Constructor ----------------

Rocket::Rocket()
    : altitude(0.0),
      velocity(0.0),
      acceleration(0.0),
      fuelMass(20.0),
      dryMass(50.0),
      thrust(2500.0),
      burnRate(20.0 / 8.0),
      rocketDragCoefficient(0.75),
      rocketReferenceArea(0.05),
      parachuteDragCoefficient(1.5),
      parachuteArea(30.0),
      parachuteDeployed(false),
      airDensity(1.225),
      gravity(9.81)
{
}

// ---------------- Public API ----------------

void Rocket::TimeStep(double dt) {
    UpdateFuel(dt);

    const double mass = ComputeMass();

    // Thrust
    double thrustAcceleration = 0.0;
    if (fuelMass > 0.0) {
        thrustAcceleration = ComputeThrustAcceleration(mass);
    }

    // Parachute logic
    DeployParachuteIfNeeded();

    // Drag
    double dragAcceleration = 0.0;
    if (parachuteDeployed) {
        dragAcceleration =
            ComputeDrag(parachuteDragCoefficient, parachuteArea) / mass;
    } else {
        dragAcceleration =
            ComputeDrag(rocketDragCoefficient, rocketReferenceArea) / mass;
    }

    // Net acceleration
    acceleration = thrustAcceleration - gravity + dragAcceleration;

    // Integrate
    velocity += acceleration * dt;
    altitude += velocity * dt;

    // Simple ground constraint
    if (altitude < 0.0) {
        altitude = 0.0;
        velocity = 0.0;
    }
}

double Rocket::GetAltitude() const {
    return altitude;
}

double Rocket::GetVelocity() const {
    return velocity;
}

double Rocket::GetAcceleration() const {
    return acceleration;
}

double Rocket::GetFuelMass() const {
    return fuelMass;
}

// ---------------- Private helpers ----------------

double Rocket::ComputeMass() const {
    return dryMass + fuelMass;
}

double Rocket::ComputeThrustAcceleration(double mass) const {
    return thrust / mass;
}

double Rocket::ComputeDrag(double dragCoefficient,
                           double referenceArea) const {
    return -0.5
           * airDensity
           * dragCoefficient
           * referenceArea
           * velocity
           * std::abs(velocity);
}

void Rocket::UpdateFuel(double dt) {
    if (fuelMass <= 0.0) {
        fuelMass = 0.0;
        return;
    }

    const double fuelBurned = burnRate * dt;
    fuelMass -= fuelBurned;

    if (fuelMass < 0.0) {
        fuelMass = 0.0;
    }
}

void Rocket::DeployParachuteIfNeeded() {
    if (!parachuteDeployed && velocity < 0.0) {
        parachuteDeployed = true;
    }
}
