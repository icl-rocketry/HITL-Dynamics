#include "SimplePropulsion.hpp"
#include "OneDRocket.hpp"
#include "IsaEnvironment.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <Eigen/Dense>
using namespace std;

int main() {
    /*double total_propmass = 24.4;  // kg
    double drymass = 60.2;         // kg

    SimplePropulsion engine("Thrust_curve.csv");
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
    */

    double total_propmass = 24.4;  
    double drymass = 60.2;        
    double area = 0.01;

    SimplePropulsion engine("Thrust_curve.csv");
    DragFromFile aero("cd.csv");
    IsaEnvironment env;
    OneDRocket rocket(drymass, total_propmass, area, engine, aero, env);
    State current(3);
    current[0] = 0.0;                    
    current[1] = 0.0;                    
    current[2] = drymass + total_propmass; 

    double t = 0.0;

     std::ofstream outFile("rocket_log.csv");

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open file!" << std::endl;
        return -1;
    }

    outFile << "t,h,v,m\n";

    while (t < 70.0)
    {
        Eigen::VectorXd derivativeVec = rocket.GetDerivatives(current);

        State derivative(3);
        derivative.data = derivativeVec;

        current = rocket.GetnewRocketState(current, derivative);

        outFile << t << ","
                << current[0] << ","
                << current[1] << ","
                << current[2] << "\n";

        t += dt;
    }

    outFile.close();
    cout << "Simulation finished. Data saved to rocket_log.csv" << endl;

    return 0;
}
