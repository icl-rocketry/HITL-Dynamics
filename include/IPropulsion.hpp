#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
constexpr double g = 9.81;
using namespace std;

class IPropulsion {

private:
    vector<double> time;
    vector<double> thrust;

    void readtable(const string& filename);

public:
    IPropulsion();

    explicit IPropulsion(const string& filename);

    double GetThrust(double current_time);

    double calculate_total_impulse( ) const;

    double GetISP(double total_propmass);

    double Get_PropMass(double total_propmass, double t);

    double Get_Drymass(double drymass);
};