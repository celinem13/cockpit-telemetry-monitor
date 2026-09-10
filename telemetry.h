#ifndef TELEMETRY_H
#define TELEMETRY_H

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

class TelemetrySimulator {
public:
    TelemetryReading nextReading();

private:
    int simulationStep{0};
};

WarningStatus evaluateWarnings(
    const TelemetryReading& reading,
    double highEngineTemperatureCelsius,
    double lowFuelPercent
);

#endif