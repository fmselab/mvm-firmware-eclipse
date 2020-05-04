cmake_minimum_required(VERSION 3.5)

project(mvm_unittests LANGUAGES CXX VERSION 0.1.0)

# find_package(Catch2 REQUIRED)
add_subdirectory(libs/Catch2)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/libs/Catch2/contrib")

set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage --coverage")

add_executable(mvm_unittests
    src/stdlib_noniso.cpp
    src/WString.cpp

    fw/MVMFirmwareCpp/MVMFirmwareCore/DebugIface.cpp

    # Venturi Flow Meter
    test/test_driver_venturi_flow_meter.cpp
    fw/MVMFirmwareCpp/MVMFirmwareCore/driver_VenturiFlowMeter.cpp

    # MS5525DSO Pressure Sensor
    test/test_driver_5525dso.cpp
    fw/MVMFirmwareCpp/MVMFirmwareCore/driver_5525DSO.cpp

    # MVM
    # test/test_mvm.cpp
    # fw/MVMFirmwareCore/MVMCore.cpp
    # fw/MVMFirmwareCore/HAL.cpp

    # Test runner entry point
    test/test_main.cpp
)

include_directories(
    "src"
    "libs/trompeloeil/include"
    "fw/MVMFirmwareCpp/MVMFirmwareCore"
)

target_compile_features(mvm_unittests PUBLIC cxx_std_14)
target_compile_definitions(mvm_unittests PUBLIC -DARDUINO=100)
target_link_libraries(mvm_unittests Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(mvm_unittests)

find_program(GCOVR "gcovr")
if(GCOVR)
add_custom_command(TARGET mvm_unittests POST_BUILD
    COMMAND gcovr -r build -f '/.*/fw' -e '.*\.h' --html --html-details -o ${CMAKE_CURRENT_SOURCE_DIR}/report/coverage.html
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running gcovr..."
)
ENDIF()
