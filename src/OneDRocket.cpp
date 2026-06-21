#include "OneDRocket.hpp"
#include <cmath>
using namespace std;

OneDRocket::OneDRocket(double drymass_input, double totalpropmass_input, double area_input, SimplePropulsion& engine_input, DragFromFile& aero_input, IsaEnvironment& env_input)
    :totalpropmass(totalpropmass_input), area(area_input), engine(engine_input), aero(aero_input), env(env_input), dState(3), AerodynamicState(1)
    {
        drymass = drymass_input;
        totalmass = drymass + totalpropmass_input;
        AerodynamicState[0] = Machinput;
    }

Eigen::VectorXd OneDRocket::GetDerivatives(const State& current)
    {
        double x = 0.0;  
        double x_dot = 0.0; 
        double m_dot = 0.0;
        x = current[0];
        x_dot = current[1];
        totalmass = current[2];

        double T = engine.GetThrust();
        double Isp = engine.GetISP(totalpropmass);

        x = current[0];
        x_dot = current[1];
        totalmass = current[2];

        if (Isp > 0.0)
        {
            m_dot = T / (Isp * g);
        }       
        else
        {
            m_dot = 0.0;
        }

        if (totalmass <= drymass)
        {
            T = 0.0;
            m_dot = 0.0;
        }

        double a = env.GetSpeedOfSound(x);
        if (a > 0.0)
        {       
            Machinput = abs(x_dot) / a;
        }
        else
        {
            Machinput = 0.0;
        }

        AerodynamicState[0] = Machinput;
        double cd = aero.GetCd(AerodynamicState);
        double rho_air = env.GetDensity(x);
        double D = 0.5 * rho_air * area * pow(x_dot,2) * cd;
        if (x_dot > 0)
        {
            D = -D;
        }
        else if (x_dot == 0)
        {
            D = 0.0;
        }       
        double x_ddot = (T + D - totalmass * g)/totalmass;

        dState[0] = x_dot;
        dState[1] = x_ddot;
        dState[2] = -m_dot;
        return dState.data;
    }

    State OneDRocket::GetnewRocketState(const State& current, const State& derivative)
    {
        State next = current + derivative * dt;
        if (next[2] < drymass)
        {
            next[2] = drymass;
        }

        if (next[0] <= 0)
        {
            next[0] = 0;

            if (next[1] < 0)
            {
                next[1] = 0; 
            }
        }
        return next;
    }

    double OneDRocket::GetMass(double) const
    {   
        return RocketState[2];
    }