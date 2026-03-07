#include "../../include/IsaWrapper.hpp"
#include <iostream>
#include <cmath>
#include <Eigen/Dense>



/*double IsaWrapper::GetTemperature (double alt){
	auto test = LouiEriksson::ISA<double>::TrySolve(alt);

	if (test.has_value()){
		return test->m_Temperature;
	} else {
		throw std::out_of_range("Error: Altitude out of bounds.");
	}
};
*/
double IsaWrapper::GetDensity (double alt) const{
	auto test = LouiEriksson::ISA<double>::TrySolve(alt);

	if (test.has_value()){
		return test->m_Density;
	} else {
		throw std::out_of_range("Error: Altitude out of bounds.");
	}
};
double IsaWrapper::GetPressure (double alt) const{
	auto test = LouiEriksson::ISA<double>::TrySolve(alt);

	if (test.has_value()){
		return test->m_Pressure;
	} else {
		throw std::out_of_range("Error: Altitude out of bounds.");
	}
};
double IsaWrapper::GetSpeedOfSound (double alt) const{
	auto test = LouiEriksson::ISA<double>::TrySolve(alt);

	if (test.has_value()){
		double C = 20.05 * std::sqrt(test->m_Temperature);
		return C;
	} else {
		throw std::out_of_range("Error: Altitude out of bounds.");
	}
};


Eigen::Vector3d IsaWrapper::GetGravityVector(const Eigen::Vector3d& position) const {
	Eigen::Vector3d colVec;
    colVec << 0, 0, 0; //not needed so set to 0

	return colVec;
};

Eigen::Vector3d IsaWrapper::GetWind(double altitude) const {
		Eigen::Vector3d colVec;
    colVec << 0, 0,0; //not needed so set to 0
	return colVec;
};



