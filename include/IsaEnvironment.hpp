#pragma once

#include "IEnvironment.hpp"

// ISA atmosphere + simple gravity/wind model.
class IsaEnvironment final : public IEnvironment {
public:
    IsaEnvironment() = default;
    ~IsaEnvironment() override = default;

    double GetDensity(double altitude) const override;
    double GetPressure(double altitude) const override;
    double GetSpeedOfSound(double altitude) const override;
    Eigen::Vector3d GetGravityVector(const Eigen::Vector3d& position) const override;
    Eigen::Vector3d GetWind(double altitude) const override;

private:
    // Shared helper so all public atmosphere methods use the same altitude-layer logic.
    double GetTemperature(double altitude) const;

    // Centralising all constants required for calcualtions.
    static constexpr double seaLevelPressure = 101325.0;
    static constexpr double seaLevelTemperature = 288.15;
    static constexpr double temperatureLapseRate = 0.0065;
    static constexpr double gasConstantAir = 287.05;
    static constexpr double heatCapacityRatio = 1.4;

    static constexpr double gravitationalParameter = 3.986004418e14;
    static constexpr double gravityMagnitude = 9.80665;
};
