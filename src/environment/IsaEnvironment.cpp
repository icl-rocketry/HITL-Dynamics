#include "IsaEnvironment.hpp"
#include <cmath>

double IsaEnvironment::GetTemperature(double altitude) const {
    // Clamp to sea level because sensor/initialization noise can produce slightly negative altitude.
    const double clampedAltitude = altitude < 0.0 ? 0.0 : altitude;
    if (clampedAltitude <= 11000.0) {
        return seaLevelTemperature - temperatureLapseRate * clampedAltitude;
    }

    // Keep the 11-20 km layer isothermal to match baseline ISA behavior.
    return 216.65;
}

double IsaEnvironment::GetPressure(double altitude) const {
    const double clampedAltitude = altitude < 0.0 ? 0.0 : altitude;

    // Use the 11 km boundary temperature and pressure to keep continuity.
    const double temperatureAt11Km = seaLevelTemperature - temperatureLapseRate * 11000.0;
    const double pressureAt11Km = seaLevelPressure *
        std::pow(
            temperatureAt11Km / seaLevelTemperature,
            gravityMagnitude / (gasConstantAir * temperatureLapseRate));

    if (clampedAltitude <= 11000.0) {
        const double temperature = seaLevelTemperature - temperatureLapseRate * clampedAltitude;
        return seaLevelPressure *
            std::pow(
                temperature / seaLevelTemperature,
                gravityMagnitude / (gasConstantAir * temperatureLapseRate));
    }

    return pressureAt11Km *
        std::exp(
            -gravityMagnitude * (clampedAltitude - 11000.0) /
            (gasConstantAir * temperatureAt11Km));
}

double IsaEnvironment::GetDensity(double altitude) const {
    const double pressure = GetPressure(altitude);
    const double temperature = GetTemperature(altitude);
    return pressure / (gasConstantAir * temperature);
}

double IsaEnvironment::GetSpeedOfSound(double altitude) const {
    const double temperature = GetTemperature(altitude);
    return std::sqrt(heatCapacityRatio * gasConstantAir * temperature);
}

Eigen::Vector3d IsaEnvironment::GetGravityVector(const Eigen::Vector3d& position) const {
    const double radiusSquared = position.squaredNorm();
    if (radiusSquared < 1.0e-9) {
        // Protect against divide-by-zero when position is not yet initialized.
        return Eigen::Vector3d(0.0, 0.0, -gravityMagnitude);
    }

    const double radius = std::sqrt(radiusSquared);
    return -gravitationalParameter * position / (radius * radius * radius);
}

Eigen::Vector3d IsaEnvironment::GetWind(double altitude) const {
    // Returns no wind vector until a wind model is developed.
    (void)altitude;
    return Eigen::Vector3d::Zero();
}
