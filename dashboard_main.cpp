#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    QWidget window;
    window.setWindowTitle("Cockpit Telemetry Monitor");
    window.resize(600, 400);

    window.setStyleSheet(
        "QWidget {"
        "  background-color: #101820;"
        "  color: #eaf2f8;"
        "}"
        "QLabel {"
        "  font-size: 18px;"
        "  padding: 6px;"
        "}"
    );

    auto* layout = new QVBoxLayout(&window);

    auto* titleLabel = new QLabel("Cockpit Telemetry Monitor");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "font-size: 26px;"
        "font-weight: bold;"
        "color: #55d6ff;"
    );

    layout->addWidget(titleLabel);
    layout->addWidget(new QLabel("Airspeed: waiting for telemetry"));
    layout->addWidget(new QLabel("Altitude: waiting for telemetry"));
    layout->addWidget(new QLabel("Heading: waiting for telemetry"));
    layout->addWidget(new QLabel("Engine temperature: waiting for telemetry"));
    layout->addWidget(new QLabel("Fuel: waiting for telemetry"));

    window.show();

    return application.exec();
}