cmake_minimum_required(VERSION 3.16)

project(CockpitTelemetryMonitor LANGUAGES CXX)

include(CTest)

add_library(
    telemetry_core
    telemetry.cpp
)

target_include_directories(
    telemetry_core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(
    telemetry_core
    PUBLIC
    cxx_std_17
)

target_compile_options(
    telemetry_core
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(
    telemetry_monitor
    main.cpp
)

target_link_libraries(
    telemetry_monitor
    PRIVATE
    telemetry_core
)

target_compile_options(
    telemetry_monitor
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

if(BUILD_TESTING)
    add_executable(
        telemetry_tests
        tests/telemetry_tests.cpp
    )

    target_link_libraries(
        telemetry_tests
        PRIVATE
        telemetry_core
    )

    target_compile_options(
        telemetry_tests
        PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

    add_test(
        NAME telemetry_warning_tests
        COMMAND telemetry_tests
    )
endif()