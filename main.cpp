#include <iostream>

struct TelemetryReading {
    double airspeedKnots;
    double altitudeFeet;
    double headingDegrees;
    double engineTemperatureCelsius;
    double fuelPercent;
};

struct WarningStatus {
    bool engineTemperatureHigh;
    bool fuelLow;
};

WarningStatus evaluateWarnings(
    const TelemetryReading& reading,
    double highEngineTemperatureCelsius,
    double lowFuelPercent
) {
    return {
        reading.engineTemperatureCelsius >=
            highEngineTemperatureCelsius,
        reading.fuelPercent <= lowFuelPercent
    };
}

void displayWarnings(const WarningStatus& warnings) {
    std::cout << "\nWarnings:\n";

    bool hasWarning = false;

    if (warnings.engineTemperatureHigh) {
        std::cout << "- Engine temperature is too high!\n";
        hasWarning = true;
    }

    if (warnings.fuelLow) {
        std::cout << "- Fuel level is too low!\n";
        hasWarning = true;
    }

    if (!hasWarning) {
        std::cout << "- None\n";
    }
}

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

    const WarningStatus warnings = evaluateWarnings(
        reading,
        highEngineTemperatureCelsius,
        lowFuelPercent
    );

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

    displayWarnings(warnings);

    return 0;
}