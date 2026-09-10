#include "telemetry.h"

#include <cassert>
#include <iostream>

int main() {
    const double highTemperature = 105.0;
    const double lowFuel = 20.0;

    const WarningStatus normal = evaluateWarnings(
        TelemetryReading{430.0, 12000.0, 90.0, 98.0, 75.0},
        highTemperature,
        lowFuel
    );

    assert(!normal.engineTemperatureHigh);
    assert(!normal.fuelLow);

    const WarningStatus highTemperatureOnly = evaluateWarnings(
        TelemetryReading{430.0, 12000.0, 90.0, 105.0, 75.0},
        highTemperature,
        lowFuel
    );

    assert(highTemperatureOnly.engineTemperatureHigh);
    assert(!highTemperatureOnly.fuelLow);

    const WarningStatus lowFuelOnly = evaluateWarnings(
        TelemetryReading{430.0, 12000.0, 90.0, 98.0, 20.0},
        highTemperature,
        lowFuel
    );

    assert(!lowFuelOnly.engineTemperatureHigh);
    assert(lowFuelOnly.fuelLow);

    const WarningStatus bothWarnings = evaluateWarnings(
        TelemetryReading{430.0, 12000.0, 90.0, 108.0, 16.0},
        highTemperature,
        lowFuel
    );

    assert(bothWarnings.engineTemperatureHigh);
    assert(bothWarnings.fuelLow);

    std::cout << "All telemetry warning tests passed.\n";

    return 0;
}