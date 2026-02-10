#include "Aerodynamics.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;

int main() {
    string input = " ";
    double M_input = 0.0;

    Aerodynamics aero;
    aero.readtable("cd.csv");
    double MinMach = aero.GetminMach();
    double MaxMach = aero.GetmaxMach();

    try{
        cout << "enter a Mach Number(" << MinMach << "<= M <=" << MaxMach << "): ";
        getline(cin, input);
        M_input = stod(input);
        if (M_input < 0.00 || M_input > 3.00) throw logic_error (" Value of Mach number should be in the range");
    }
    catch(const exception& e)
    {
        cout << "Error in the input" << e.what() << endl;
        return 1;
    }

    State state(1);
    state[0] = M_input;

    double cd = aero.GetCd(state);

    cout << fixed << setprecision(5);
    cout << "Drag coefficient: " << cd << endl;

    return 0;
}
