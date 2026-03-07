#include <iostream>

#include "./include/IsaWrapper.hpp"



int main() {

    double atm = 1000;
    IsaWrapper Atmos;
    std::cout << Atmos.GetPressure(atm) << std::endl;
    std::cout << Atmos.GetDensity(atm) << std::endl;
    std::cout << Atmos.GetSpeedOfSound(atm) << std::endl;
    
}