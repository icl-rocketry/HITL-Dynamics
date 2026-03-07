#include "../src/environment/ISA.hpp"
#include "./IEnvironment.hpp"
#include <iostream>


class IsaWrapper : public IEnvironment{
public:
	double GetPressure (double alt) const override;

	double GetSpeedOfSound (double alt) const override;

	double GetDensity (double alt) const override;

	double GetTemperature (double alt) const;

	virtual Eigen::Vector3d GetGravityVector(const Eigen::Vector3d& position) const override;
    
    // Returns wind velocity vector (e.g., for crosswind calculations)
    virtual Eigen::Vector3d GetWind(double altitude) const override;
};
