#pragma once
#include <Eigen/Dense>

class IEnvironment {
public:
    virtual ~IEnvironment() = default;
    
    virtual double GetDensity(double altitude) const = 0;
    virtual double GetPressure(double altitude) const = 0;
    virtual double GetSpeedOfSound(double altitude) const = 0;
    
    // Returns gravity vector based on 3D position
    virtual Eigen::Vector3d GetGravityVector(const Eigen::Vector3d& position) const = 0;
    
    // Returns wind velocity vector (e.g., for crosswind calculations)
    virtual Eigen::Vector3d GetWind(double altitude) const = 0;
};