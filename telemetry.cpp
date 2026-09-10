#include "telemetry.h"

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