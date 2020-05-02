cmake_minimum_required(VERSION 3.5)

project(mvm_unittests LANGUAGES CXX VERSION 0.1.0)

# find_package(Catch2 REQUIRED)
add_subdirectory(libs/Catch2)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/libs/Catch2/contrib")
add_executable(mvm_unittests
    test_driver_venturi_flow_meter.cpp
    ../MVMFirmwareCpp/MVMFirmwareCore/driver_VenturiFlowMeter.cpp
)
include_directories(
    "."
    "libs/trompeloeil"
    "../MVMFirmwareCpp/MVMFirmwareCore"
    )
target_link_libraries(mvm_unittests Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(mvm_unittests)
