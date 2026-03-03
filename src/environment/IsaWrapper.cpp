#include "IsaWrapper.hpp"
#include <iostream>
#include <cmath>





double GetTemperature (double alt){
	auto test = LouiEriksson::ISA<double>::TrySolve(alt);

	if (test.has_value()){
		return test->m_Temperature;
	} else {
		throw std::out_of_range("Error: Altitude out of bounds.");
	}
};
double GetDensity (double alt){
	auto test = LouiEriksson::ISA<double>::TrySolve(alt);

	if (test.has_value()){
		return test->m_Density;
	} else {
		throw std::out_of_range("Error: Altitude out of bounds.");
	}
};
double GetPressure (double alt){
	auto test = LouiEriksson::ISA<double>::TrySolve(alt);

	if (test.has_value()){
		return test->m_Pressure;
	} else {
		throw std::out_of_range("Error: Altitude out of bounds.");
	}
};
double GetSpeedOfSound (double alt) {
	auto test = LouiEriksson::ISA<double>::TrySolve(alt);

	if (test.has_value()){
		double C = 20.05 * std::sqrt(test->m_Temperature);
		return C;
	} else {
		throw std::out_of_range("Error: Altitude out of bounds.");
	}
};



