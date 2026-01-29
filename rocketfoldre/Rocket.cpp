#pragma once

class Rocket1DoF {
private:
    const double g = 9.81;
    const double CoD = 0.6;
    double velocity = 0;
    double acceleration = 0;
    double force = 4000;
    double dry_mass = 50;
    double fuel_mass = 20;
    double burnRate = 20.0 / 8.0;

    double ComputeMass() const {
        return dry_mass + fuel_mass;
    }

    double rocketInitalThrust(double total_mass) const{
        return force / total_mass;
    }
    void UpdateVelocity(double dt, double thrust_acceleration){
        
        velocity += (thrust_acceleration-g)*dt;
    }

    

    

public:
    void TimeStep(double dt){
        double thrust_acceleration;
        UpdateVelocity(dt, thrust_acceleration);
    }
    void UpdateFuel(double dt) {
        if(fuel_mass <= 0.0)
            return;
        
        double fuelBurned = burnRate * dt;
        if(fuelBurned > fuel_mass)
            fuelBurned = fuel_mass;

        fuel_mass -= fuelBurned;
    }

    


};
