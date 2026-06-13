#pragma once
#include <vector>
#include <string>

class IPropulsion {
public:
virtual~ IPropulsion() = default;

virtual double calculate_total_impulse( ) const = 0;

virtual double GetISP(double total_propmass) = 0;

virtual double GetThrust() = 0;

virtual double Get_PropMass(double total_propmass, double current_thrust) = 0;

virtual double Get_Drymass(double drymass) = 0;

virtual void SetInitialMass(double totalmass) = 0;
};