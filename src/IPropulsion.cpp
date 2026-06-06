#include "IPropulsion.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

IPropulsion::IPropulsion() = default;

IPropulsion::IPropulsion(const string& filename)
    {
        readtable(filename);
    }

void IPropulsion::readtable(const string& filename)
    {
        ifstream vMyFile(filename);
        if (!vMyFile.good())
        {
            throw runtime_error("Fail to open the file: " + filename);
            return;
        }

        time.clear();
        thrust.clear();

        double time_data;
        double thrust_data;
        char comma;

        vector<pair<double, double>> data;
        while (vMyFile >> time_data >> comma >> thrust_data)
        {
            if (vMyFile.fail())
                break;

            if (comma != ',')
                continue; 

            if (time_data < 0)
                continue;

            if (thrust_data < 0)
                thrust_data = 0;

            data.emplace_back(time_data, thrust_data);
        }

        vMyFile.close();

        if (data.empty())
        return;

        sort(data.begin(), data.end(), [](const pair<double, double>& a, const pair<double, double>& b){return a.first < b.first;});

        for (const auto& p : data)
        {
            time.push_back(p.first);
            thrust.push_back(p.second);
        }
    }

    double IPropulsion::GetThrust(double current_time)
    {
        if ( time.empty() || thrust.empty() )
            return 0.0;

        if ( current_time <= time[0] )
            return thrust[0];

        if ( current_time >= time.back() )
            return thrust.back();

        for (size_t i = 0; i < time.size() - 1; i++)
        {
            if ( current_time >= time[i] && current_time <= time[i+1] )
            {
                double t = (current_time - time[i]) / (time[i+1] - time[i]);
                return thrust[i] + t * (thrust[i+1] - thrust[i]);
            }
        }
        return 0.0;
    }

    double IPropulsion::calculate_total_impulse( ) const
    {
        if (time.size() != thrust.size())
        {
            throw runtime_error("Time and thrust size mismatch");
        }

        double total_Impulse = 0.0;
        for (size_t i = 0; i < time.size() - 1; i++)
        {
            double dt = time[i + 1] - time[i];
            double average_T = (thrust[i + 1] + thrust[i]) / 2.0;
            total_Impulse += average_T * dt;
        }
        return total_Impulse;
    }
    
    double IPropulsion::GetISP(double total_propmass)
    {
        double total_Impulse = calculate_total_impulse( );
        return total_Impulse / (total_propmass * g);
    }

    double IPropulsion::Get_PropMass(double total_propmass, double t)
    {
        double burn_time = time.back() - time.front();

        if (burn_time <= 0)
            throw runtime_error("Invalid burn time");

        if (t <= 0)
            return total_propmass;
        
        if (t >= burn_time)
            return 0.0;

        double PropMass_flow = total_propmass / burn_time;
        return total_propmass - PropMass_flow * t;
    }

    double IPropulsion::Get_Drymass(double drymass)
    {
        double m_drymass = drymass;
        return m_drymass;
    }