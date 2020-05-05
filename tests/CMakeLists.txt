cmake_minimum_required(VERSION 3.5)

project(mvm_unittests LANGUAGES CXX VERSION 0.1.0)

# find_package(Catch2 REQUIRED)
add_subdirectory(libs/Catch2)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/libs/Catch2/contrib")

set(GCOV_LINK_FLAGS "-lgcov --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCOV_LINK_FLAGS}")
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_CXX_EXTENSIONS OFF)

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

    # Sensirion SFM3019 Flow Sensor
    test/test_driver_sfm3019.cpp
    fw/MVMFirmwareCpp/MVMFirmwareCore/driver_SFM3019.cpp

    # ADS1115 Analog-to-Digital Converter
    # Uncomment if patch is being used, or file has been fixed to work with mock
    #test/test_driver_ads1115.cpp
    #fw/MVMFirmwareCpp/MVMFirmwareCore/driver_ADS1115.cpp

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

# Patches in replacement files
add_custom_target(mvm_unittests_patched
    COMMAND cp
    # Add any files that need to be 'patched' to work on this line
    ${CMAKE_CURRENT_SOURCE_DIR}/hotfix/hw.h
    # THIS IS A HACK FOR DEMONSTRATION PURPOSES. driver_ADS1115.cpp should
    # NOT be normally 'patched', but it has errors in it currently that make it
    # untestable. Uncomment this to work on the 'patched' version to prep for proper file
    # ${CMAKE_CURRENT_SOURCE_DIR}/hotfix/driver_ADS1115.cpp

    # Destination
    ${CMAKE_CURRENT_SOURCE_DIR}/fw/MVMFirmwareCpp/MVMFirmwareCore
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
# Add patch target as dependency, so that it gets executed before source compilation
add_dependencies(mvm_unittests mvm_unittests_patched)

include(CTest)
include(Catch)
catch_discover_tests(mvm_unittests)

#find_program(GCOVR "gcovr")
#if(GCOVR)
# #Force run of ctest to generate coverage report files
# add_custom_command(TARGET mvm_unittests POST_BUILD
#     COMMAND ctest
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
#     COMMENT "Running ctest for gcovr"
#)
#
## Generate gcovr html report, filtering out .H files and everything not in fw/
#add_custom_command(TARGET mvm_unittests POST_BUILD
#    COMMAND gcovr -r . -f '/.*/fw' -e '.*\.h' --html --html-details -o report/coverage.html -s
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#    COMMENT "Running gcovr..."
#)
#ENDIF()

#find_program(CPPCHECK "cppcheck")
#if(CPPCHECK)
## Generate cppcheck static analysis report
#add_custom_command(TARGET mvm_unittests POST_BUILD
#    COMMAND cppcheck --quiet -ibuild -itest -ilibs -Ifw/MVMFirmwareCpp/MVMFirmwareCore --language=c++ --enable=all --xml --xml-version=2 . 2> report/cppcheck-result.xml
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#    COMMENT "Running cppcheck"
#
#    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/libs/cppcheck/htmlreport/cppcheck-htmlreport --source-encoding="iso8859-1" --report-dir=report --file=report/cppcheck-result.xml --title=MVM --source-dir=.
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#    COMMENT "Running cppcheck-htmlreport"
#)
#ENDIF()
