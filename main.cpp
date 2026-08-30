#include <iostream>

int main() {
    const double airspeedKnots = 430.0;
    const double altitudeFeet = 12000.0;
    const double headingDegrees = 90.0;
    const double engineTemperatureCelsius = 98.0;
    const double fuelPercent = 75.0;

    const double highEngineTemperatureCelsius = 105.0;
    const double lowFuelPercent = 20.0;

    std::cout << "Cockpit Telemetry Monitor\n";
    std::cout << "---------------------------\n";
    std::cout << "Airspeed: " << airspeedKnots << " knots\n";
    std::cout << "Altitude: " << altitudeFeet << " feet\n";
    std::cout << "Heading: " << headingDegrees << " degrees\n";
    std::cout << "Engine temperature: "
              << engineTemperatureCelsius << " C\n";
    std::cout << "Fuel: " << fuelPercent << "%\n";

    std::cout << "\nWarnings:\n";

    bool hasWarning = false;

    if (engineTemperatureCelsius >= highEngineTemperatureCelsius) {
        std::cout << "- Engine temperature is too high!\n";
        hasWarning = true;
    }

    if (fuelPercent <= lowFuelPercent) {
        std::cout << "- Fuel level is too low!\n";
        hasWarning = true;
    }

    if (!hasWarning) {
        std::cout << "- None\n";
    }

    return 0;
}