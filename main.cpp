#include "IPropulsion.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdexcept>
using namespace std;

int main() {
    double total_propmass = 24.4;  // kg
    double drymass = 60.2;         // kg

    IPropulsion engine("Thrust_curve.csv");
    engine.SetInitialMass(total_propmass);

    double time = 0.0;
    double total_mass = total_propmass + drymass;

    cout << fixed << setprecision(5);
    cout << "Start simulation...\n\n";

    while (time <= 10)
    {
        double thrust = engine.GetThrust();
        double remaining_prop = engine.Get_PropMass(total_propmass, thrust);
        total_mass = drymass + remaining_prop;

        cout << "t = " << time << " s"
             << ", Thrust = " << thrust << " N"
             << ", Prop mass = " << remaining_prop << " kg"
             << ", Total mass = " << total_mass << " kg"
             << endl;

        time += 0.01;
    }


    cout << "\n===== FINAL RESULT =====\n";
    double final_prop = engine.Get_PropMass(total_propmass, 0.0);

    cout << "Final propellant mass: " << final_prop << " kg\n";
    cout << "Dry mass: " << drymass << " kg\n";
    cout << "Total impulse: " << engine.calculate_total_impulse() << " N*s\n";
    cout << "Final vehicle mass: " << drymass + final_prop << " kg\n";

    return 0;
}
