cmake_minimum_required(VERSION 3.16)

project(CockpitTelemetryMonitor LANGUAGES CXX)

add_executable(telemetry_monitor main.cpp)

target_compile_features(
    telemetry_monitor
    PRIVATE
    cxx_std_17
)

target_compile_options(
    telemetry_monitor
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)