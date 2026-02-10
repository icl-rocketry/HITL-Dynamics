#pragma once

class Rocket {
public:
    Rocket();

    void TimeStep(double dt);

    double GetAltitude() const;
    double GetVelocity() const;
    double GetAcceleration() const;
    double GetFuelMass() const;

private:
    // ----- State -----
    double altitude;
    double velocity;
    double acceleration;
    double fuelMass;

    // ----- Rocket parameters -----
    double dryMass;
    double thrust;
    double burnRate;

    // ----- Aerodynamics (rocket body) -----
    double rocketDragCoefficient;
    double rocketReferenceArea;

    // ----- Parachute parameters -----
    double parachuteDragCoefficient;
    double parachuteArea;
    bool parachuteDeployed;

    // ----- Environment (temporary) -----
    double airDensity;
    double gravity;

    // ----- Physics helpers -----
    double ComputeMass() const;
    double ComputeThrustAcceleration(double mass) const;
    double ComputeDrag(double dragCoefficient, double referenceArea) const;

    void UpdateFuel(double dt);
    void DeployParachuteIfNeeded();
};
