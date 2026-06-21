#include "SimplePropulsion.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
using namespace std;

SimplePropulsion::SimplePropulsion() = default;

SimplePropulsion::SimplePropulsion(const string& filename)
    {
        readtable(filename);
        GetThrustTable();
    }

    
void SimplePropulsion::readtable(const string& filename)
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


    void SimplePropulsion::GetThrustTable()
    {
        if (time.empty() || thrust.empty())
            return;

        double burn_time = time.back() - time.front();

        int steps = static_cast<int>(burn_time / dt);
        pre_cal_Thrust.resize(steps + 1);

        constexpr double eps = 1e-8;

        for (int i = 0; i <= steps; i++)
        {
            double t = i * dt;

            if (t <= time.front())
            {
                pre_cal_Thrust[i] = thrust.front();
                continue;
            }

            if (t >= time.back())
            {
                pre_cal_Thrust[i] = thrust.back();
                continue;
            }

            for (size_t j = 0; j < time.size() - 1; j++)
            {
                if (t >= time[j] && t <= time[j + 1])
                {
                    if (fabs(t - time[j]) < eps)
                    {
                        pre_cal_Thrust[i] = thrust[j];
                    }
                    else
                    {
                        double inter_t = (t - time[j]) / (time[j + 1] - time[j]);
                        pre_cal_Thrust[i] = thrust[j] + inter_t * (thrust[j + 1] - thrust[j]);
                    }
                    break;
                }
            }
        }
    }


    double SimplePropulsion::GetThrust()
    {
        if (pre_cal_Thrust.empty())
            return 0.0;

        if (index >= pre_cal_Thrust.size())
            return 0.0;

        return pre_cal_Thrust[index++];
    }


    double SimplePropulsion::calculate_total_impulse() const
    {
        if (pre_cal_Thrust.empty())
            return 0.0;

        double total_Impulse = 0.0;

        for (size_t i = 0; i < pre_cal_Thrust.size() - 1; i++)
        {
            double average_T = (pre_cal_Thrust[i] + pre_cal_Thrust[i + 1]) / 2.0;
            total_Impulse += average_T * dt;
        }

        return total_Impulse;
    }


    double SimplePropulsion::GetISP(double total_propmass) 
    {
        return calculate_total_impulse() / (total_propmass * g);
    }


    void SimplePropulsion::SetInitialMass(double totalmass)
    {   
        current_mass = totalmass;
    }


    double SimplePropulsion::Get_PropMass(double total_propmass, double current_thrust) 
    {
        double ISP = GetISP(total_propmass);
        double PropMass_flow = current_thrust / (ISP * g);
        current_mass -= PropMass_flow * dt;

        if (current_mass < 0.0)
        {
            return current_mass = 0.0;
        }
        
        return current_mass;
    }
    

    double SimplePropulsion::Get_Drymass(double dry_mass) 
    {
        return dry_mass;
    }