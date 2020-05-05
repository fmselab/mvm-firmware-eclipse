# mvm-firmware-unittests

This is a temporary repository to compile and execute the MVM together with its unit tests.

For sw integration tests see: https://github.com/fmselab/mvm-firmware

It contains the unit tests written for the classes of MVM above HAL, using catch2 and trompeloeil.

## Tools required

- cmake
- GCC with c++ 14 support (required for Trompeloeil)
- gcovr

No hardware is required, only the software. The goal is to perform unit tests.

## Installation

git submodule init
git submodule update --recursive

## Running

```
cd tests/build
cmake ..
make all
make test
../run_gcovr.sh
../run_cppcheck.sh
```

The coverage reports should appear in test/report after `make all`

## File Listings

tests
    fw - contains git submodule of MVMFirmwareCPP
    build - Build directory for cmake
    libs - Contains git submodules of Catch2 and Trompeloeil
    src - Source files needed to build mock and perform unit tests
    test - unit test files

## Hotfixes

- class `HW` currently isn't a pure virtual, there is a replacement

- `driver_ADC_ADS1115.cpp` can be overwritten with a modified version that works with mock. Currently commented out.

## FAQ

- The coverage results seem incomplete

Please run the `make test` before running the `run_gcovr.sh` script, otherwise the coverage report will not be accurate
