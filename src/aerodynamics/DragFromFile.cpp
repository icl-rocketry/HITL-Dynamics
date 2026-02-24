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
        
    mach.clear();
    cd.clear();
        
    double Mach_data;
    double Cd_data;
    char comma;
        
    while (vMyFile >> Mach_data >> comma >> Cd_data)
    {
        mach.push_back(Mach_data);
        cd.push_back(Cd_data);
    }

    auto range = minmax_element(mach.begin(), mach.end());
    MinMach = *range.first;
    MaxMach = *range.second;
    vMyFile.close();
}

double DragFromFile::interpolateCD(double MachInput) const
{
    if (mach.empty()) return 0.0;
        
    for (size_t i = 0; i < mach.size() - 1; i++)
    {
    if (MachInput >= mach[i] && MachInput <= mach[i+1])
        {
            return cd[i] + (cd[i+1] - cd[i]) * (MachInput - mach[i]) / (mach[i+1] - mach[i]);
        }
    }
        
    return cd.back();
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
