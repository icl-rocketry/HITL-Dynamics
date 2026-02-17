#pragma once
#include <Eigen/Dense>

class RocketModel {
public:
    virtual ~RocketModel() = default;

    virtual double GetThrust(double t) const = 0;
    virtual Eigen::Vector3d GetThrustVector(double t) const = 0;

    virtual double GetMass(double t) const = 0;
    virtual double GetReferenceDiameter() const = 0;
    virtual double GetReferenceArea() const = 0;

    virtual Eigen::Vector3d GetCenterOfMass(double t) const = 0;
    virtual Eigen::Matrix3d GetMomentOfInertia(double t) const = 0;

    virtual double GetLength() const = 0;
};
