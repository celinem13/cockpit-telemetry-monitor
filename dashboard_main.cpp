#include "telemetry.h"

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    constexpr double highEngineTemperatureCelsius = 105.0;
    constexpr double lowFuelPercent = 20.0;

    TelemetrySimulator simulator;

    QWidget window;
    window.setWindowTitle("Cockpit Telemetry Monitor");
    window.resize(650, 450);

    window.setStyleSheet(
        "QWidget {"
        "  background-color: #101820;"
        "  color: #eaf2f8;"
        "}"
        "QLabel {"
        "  font-size: 18px;"
        "  padding: 8px;"
        "}"
        "QLabel#titleLabel {"
        "  color: #55d6ff;"
        "  font-size: 26px;"
        "  font-weight: bold;"
        "}"
        "QLabel#valueLabel {"
        "  background-color: #182a38;"
        "  border: 1px solid #2d5268;"
        "  color: white;"
        "  font-size: 22px;"
        "  font-weight: bold;"
        "}"
    );

    auto* mainLayout = new QVBoxLayout(&window);

    auto* titleLabel = new QLabel("Cockpit Telemetry Monitor");
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    auto* telemetryLayout = new QGridLayout();

    const auto createValueLabel = []() {
        auto* label = new QLabel("--");
        label->setObjectName("valueLabel");
        label->setAlignment(Qt::AlignCenter);
        return label;
    };

    auto* airspeedValueLabel = createValueLabel();
    auto* altitudeValueLabel = createValueLabel();
    auto* headingValueLabel = createValueLabel();
    auto* temperatureValueLabel = createValueLabel();
    auto* fuelValueLabel = createValueLabel();

    telemetryLayout->addWidget(new QLabel("Airspeed"), 0, 0);
    telemetryLayout->addWidget(airspeedValueLabel, 0, 1);

    telemetryLayout->addWidget(new QLabel("Altitude"), 1, 0);
    telemetryLayout->addWidget(altitudeValueLabel, 1, 1);

    telemetryLayout->addWidget(new QLabel("Heading"), 2, 0);
    telemetryLayout->addWidget(headingValueLabel, 2, 1);

    telemetryLayout->addWidget(new QLabel("Engine temperature"), 3, 0);
    telemetryLayout->addWidget(temperatureValueLabel, 3, 1);

    telemetryLayout->addWidget(new QLabel("Fuel"), 4, 0);
    telemetryLayout->addWidget(fuelValueLabel, 4, 1);

    mainLayout->addLayout(telemetryLayout);

    auto* warningLabel = new QLabel();
    warningLabel->setAlignment(Qt::AlignCenter);
    warningLabel->setWordWrap(true);
    mainLayout->addWidget(warningLabel);

    const auto updateDashboard = [&]() {
        const TelemetryReading reading = simulator.nextReading();

        const WarningStatus warnings = evaluateWarnings(
            reading,
            highEngineTemperatureCelsius,
            lowFuelPercent
        );

        airspeedValueLabel->setText(
            QString::number(reading.airspeedKnots, 'f', 1)
            + " knots"
        );

        altitudeValueLabel->setText(
            QString::number(reading.altitudeFeet, 'f', 0)
            + " feet"
        );

        headingValueLabel->setText(
            QString::number(reading.headingDegrees, 'f', 0)
            + " degrees"
        );

        temperatureValueLabel->setText(
            QString::number(
                reading.engineTemperatureCelsius,
                'f',
                1
            ) + " C"
        );

        fuelValueLabel->setText(
            QString::number(reading.fuelPercent, 'f', 1)
            + "%"
        );

        if (warnings.engineTemperatureHigh && warnings.fuelLow) {
            warningLabel->setText(
                "WARNING: Engine temperature high | Fuel low"
            );
            warningLabel->setStyleSheet(
                "background-color: #451a1a;"
                "color: #ff6b6b;"
                "font-weight: bold;"
            );
        } else if (warnings.engineTemperatureHigh) {
            warningLabel->setText(
                "WARNING: Engine temperature high"
            );
            warningLabel->setStyleSheet(
                "background-color: #451a1a;"
                "color: #ff6b6b;"
                "font-weight: bold;"
            );
        } else if (warnings.fuelLow) {
            warningLabel->setText("WARNING: Fuel low");
            warningLabel->setStyleSheet(
                "background-color: #451a1a;"
                "color: #ff6b6b;"
                "font-weight: bold;"
            );
        } else {
            warningLabel->setText("STATUS: Normal");
            warningLabel->setStyleSheet(
                "background-color: #123524;"
                "color: #7cfc98;"
                "font-weight: bold;"
            );
        }
    };

    QTimer timer;

    QObject::connect(
        &timer,
        &QTimer::timeout,
        &window,
        updateDashboard
    );

    updateDashboard();
    timer.start(500);

    window.show();

    return application.exec();
}