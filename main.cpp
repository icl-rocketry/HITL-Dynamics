#include "IPropulsion.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdexcept>
using namespace std;

int main() {
    double t = 7.0; //unit: s
    double total_propmass = 24.4; //unit: kg
    IPropulsion engine("Thrust_curve.csv");
    double T = engine.GetThrust(t);
    double total_Impulse = engine.calculate_total_impulse();
    double m_prop = engine.Get_PropMass(total_propmass, t);

    cout << fixed << setprecision(5);
    cout << "Prop mass: " << m_prop << endl;
    cout << "Thrust: " << T << endl;
    cout << "Total impulse: " << total_Impulse << endl;
    return 0;
    return 0;
}
