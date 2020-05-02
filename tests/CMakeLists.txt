cmake_minimum_required(VERSION 3.5)

project(mvm_unittests LANGUAGES CXX VERSION 0.1.0)

find_package(Catch2 REQUIRED)
add_executable(mvm_unittests
    test_driver_venturi_flow_meter.cpp
    ../MVMFirmwareCpp/MVMFirmwareCore/driver_VenturiFlowMeter.cpp
)
include_directories(
    "."
    "../MVMFirmwareCpp/MVMFirmwareCore"
    )
target_link_libraries(mvm_unittests Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(mvm_unittests)
