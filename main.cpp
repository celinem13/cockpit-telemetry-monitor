#include <iostream>

struct TelemetryReading {
    double airspeedKnots;
    double altitudeFeet;
    double headingDegrees;
    double engineTemperatureCelsius;
    double fuelPercent;
};

int main() {
    const TelemetryReading reading{
        430.0,
        12000.0,
        90.0,
        108.0,
        16.0
    };

    const double highEngineTemperatureCelsius = 105.0;
    const double lowFuelPercent = 20.0;

    std::cout << "Cockpit Telemetry Monitor\n";
    std::cout << "---------------------------\n";
    std::cout << "Airspeed: "
              << reading.airspeedKnots << " knots\n";
    std::cout << "Altitude: "
              << reading.altitudeFeet << " feet\n";
    std::cout << "Heading: "
              << reading.headingDegrees << " degrees\n";
    std::cout << "Engine temperature: "
              << reading.engineTemperatureCelsius << " C\n";
    std::cout << "Fuel: "
              << reading.fuelPercent << "%\n";

    std::cout << "\nWarnings:\n";

    bool hasWarning = false;

    if (reading.engineTemperatureCelsius >=
        highEngineTemperatureCelsius) {
        std::cout << "- Engine temperature is too high!\n";
        hasWarning = true;
    }

    if (reading.fuelPercent <= lowFuelPercent) {
        std::cout << "- Fuel level is too low!\n";
        hasWarning = true;
    }

    if (!hasWarning) {
        std::cout << "- None\n";
    }

    return 0;
}