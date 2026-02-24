#include "Aerodynamics.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

DragFromFile::DragFromFile() = default;

DragFromFile::DragFromFile(const string& filename)
{
    readTable(filename);
}

void DragFromFile::readTable(const string& filename)
{
    ifstream vMyFile(filename);
    if (!vMyFile.good())
    {
        throw runtime_error("Failed to open file: " + filename);
        return;
    }
        
    Mach.clear();
    Cd.clear();
        
    double Mach_data;
    double Cd_data;
    char comma;
        
    while (vMyFile >> Mach_data >> comma >> Cd_data)
    {
        Mach.push_back(Mach_data);
        Cd.push_back(Cd_data);
    }

    auto range = minmax_element(Mach.begin(), Mach.end());
    MinMach = *range.first;
    MaxMach = *range.second;
    vMyFile.close();
}

double DragFromFile::interpolateCD(double MachInput) const
{
    if (Mach.empty()) return 0.0;
        
    for (size_t i = 0; i < Mach.size() - 1; i++)
    {
    if (MachInput >= Mach[i] && MachInput <= Mach[i+1])
        {
            return Cd[i] + (Cd[i+1] - Cd[i]) * (MachInput - Mach[i]) / (Mach[i+1] - Mach[i]);
        }
    }
        
    return Cd.back();
}

double DragFromFile::GetmaxMach() const
{
    return MaxMach;
}


double DragFromFile::GetminMach() const
{
    return MinMach;
}

double DragFromFile::GetCd(const State& aerodynamicState) const
{
    if (aerodynamicState.size() > 0)
    {
        double mach = aerodynamicState[0];
        if (mach >= MinMach && mach <= MaxMach)
        {
            return interpolateCD(mach);
        }
        else
        {
            throw out_of_range("Mach number out of range.");
        }
    }

    throw std::invalid_argument("State is empty");
}

double DragFromFile::getCdFromMach(double mach) const
{
    return interpolateCD(mach);
}


Eigen::Vector3d DragFromFile::GetMomentCoefficients(const State&) const
{
    return Eigen::Vector3d::Zero();
}

