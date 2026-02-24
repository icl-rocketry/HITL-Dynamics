#include "Aerodynamics.hpp"
#include "State.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;

int main() {
    string input = " ";
    double MachInput = 0.0;

    DragFromFile aero("cd.csv");
    double MinMach = aero.GetminMach();
    double MaxMach = aero.GetmaxMach();

    try{
        cout << "enter a Mach Number(" << MinMach << "<= M <=" << MaxMach << "): ";
        getline(cin, input);
        MachInput = stod(input);
        if (MachInput < 0.00 || MachInput > 3.00) throw logic_error (" Value of Mach number should be in the range");
    }
    catch(const exception& e)
    {
        cout << "Error in the input" << e.what() << endl;
        return 1;
    }

    State state(1);
    state[0] = MachInput;

    double cd = aero.GetCd(state);

    cout << fixed << setprecision(5);
    cout << "Drag coefficient: " << cd << endl;
    return 0;
}
