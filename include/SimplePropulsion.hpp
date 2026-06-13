#pragma once
#include "IPropulsion.hpp"
#include <vector>
#include <string>
constexpr double g = 9.81;
using namespace std;

class SimplePropulsion : public IPropulsion {

private:
    vector<double> time;
    vector<double> thrust;
    vector<double> pre_cal_Thrust;
    size_t index = 0;
    double dt = 0.01;
    double current_mass = 0.0;

    void readtable(const string& filename);
    void GetThrustTable();

public:
    SimplePropulsion();

    explicit SimplePropulsion(const string& filename);

    double GetThrust() override;

    double calculate_total_impulse( ) const override;

    double GetISP(double total_propmass) override;

    double Get_PropMass(double total_propmass, double current_thrust) override;

    double Get_Drymass(double drymass) override;

    void SetInitialMass(double totalmass) override;
};