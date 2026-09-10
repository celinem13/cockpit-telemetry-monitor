#include "telemetry.h"

TelemetryReading TelemetrySimulator::nextReading() {
    const int step = simulationStep % 10;
    ++simulationStep;

    return {
        420.0 + step * 2.0,
        10000.0 + step * 250.0,
        static_cast<double>((90 + step * 15) % 360),
        98.0 + step * 1.5,
        40.0 - step * 3.0
    };
}

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