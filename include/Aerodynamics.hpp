#pragma once
#include "IAerodynamics.hpp"
#include "State.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

class Aerodynamics : public IAerodynamics {
private:
    vector<double> M; //Mach number
    vector<double> Cd; //Drag coefficient 
    double MaxMach = 0.0; //initialise 
    double MinMach = 0.0; //initialise 

    // Interpolation
    double interpolate(double M_input) const
    {
        if (M.empty()) return 0.0;
        
        for (size_t i = 0; i < M.size() - 1; i++)
        {
            if (M_input >= M[i] && M_input <= M[i+1])
            {
                return Cd[i] + (Cd[i+1] - Cd[i]) * (M_input - M[i]) / (M[i+1] - M[i]);
            }
        }
        
        return Cd.back();
    }

public:
    
    Aerodynamics() = default;
    
    void readtable(const string& filename)
    {
        ifstream vMyFile(filename);
        if (!vMyFile.good())
        {
            cout << "Fail to open file: " << filename << endl;
            return;
        }
        
        M.clear();
        Cd.clear();
        
        double M_data;
        double Cd_data;
        char comma;
        
        while (vMyFile >> M_data >> comma >> Cd_data)
        {
            M.push_back(M_data);
            Cd.push_back(Cd_data);
        }

        auto[minIt, maxIt] = minmax_element(M.begin(), M.end());
        MinMach = *minIt;
        MaxMach = *maxIt;

        vMyFile.close();
    }

    //Function to get Max Mach
    double GetmaxMach()
    {
        return MaxMach;
    }

    //Function to get Min Mach
    double GetminMach()
    {
        return MinMach;
    }

    // Implementation of IAerodynamics interface
    double GetCd(const State& aerodynamicState) const override
    {
        // Get Mach number from state (assuming it's the first element)
        if (aerodynamicState.size() > 0)
        {
            double mach = aerodynamicState[0];
            return interpolate(mach);
        }
        return 0.0;
    }
    
    // Direct function to get Cd from Mach (for convenience)
    double getCdFromMach(double mach) const
    {
        return interpolate(mach);
    }

    Eigen::Vector3d GetMomentCoefficients(const State& aerodynamicState) const override
    {
        return Eigen::Vector3d::Zero();
    }
};
