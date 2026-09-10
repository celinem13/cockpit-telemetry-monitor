#include "telemetry.h"

#include <chrono>
#include <iostream>
#include <thread>

void displayTelemetry(const TelemetryReading& reading) {
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
}

void displayWarnings(const WarningStatus& warnings) {
    std::cout << "Warnings:\n";

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
    constexpr double highEngineTemperatureCelsius = 105.0;
    constexpr double lowFuelPercent = 20.0;
    constexpr int numberOfUpdates = 10;

    TelemetrySimulator simulator;

    std::cout << "Cockpit Telemetry Monitor\n";
    std::cout << "===========================\n";

    for (int update = 1; update <= numberOfUpdates; ++update) {
        const TelemetryReading reading = simulator.nextReading();

        const WarningStatus warnings = evaluateWarnings(
            reading,
            highEngineTemperatureCelsius,
            lowFuelPercent
        );

        std::cout << "\nUpdate "
                  << update
                  << " of "
                  << numberOfUpdates
                  << "\n";
        std::cout << "---------------------------\n";

        displayTelemetry(reading);
        displayWarnings(warnings);

        if (update < numberOfUpdates) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(500)
            );
        }
    }

    return 0;
}