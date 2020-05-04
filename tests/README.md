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
```

The coverage reports should appear in test/report after `make all`

## File Listings

tests
    fw - contains git submodule of MVMFirmwareCPP
    build - Build directory for cmake
    libs - Contains git submodules of Catch2 and Trompeloeil
    src - Source files needed to build mock and perform unit tests
    test - unit test files

## FAQ

- I installed this and ran it and got

```
[build] CMakeFiles/mvm_unittests.dir/test/test_driver_5525dso.cpp.o: In function `HW::HW()':
[build] tests/build/../fw/MVMFirmwareCpp/MVMFirmwareCore/hw.h:16: undefined reference to `vtable for HW'
[build] CMakeFiles/mvm_unittests.dir/test/test_driver_5525dso.cpp.o:(.data.rel.ro._ZTI6MockHW[_ZTI6MockHW]+0x10): undefined reference to `typeinfo for HW'
[build] collect2: error: ld returned 1 exit status
```

What gives?

A) The `Class HW` has not yet been updated to be a pure virtual, after performing the `git submodule update` you must go and edit it to be pure virtual. Replace MVMFirmwareCpp/MVMFirmwareCore/hw.h with the following:

```
// hw.h

#ifndef _HW_h
#define _HW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "generic_definitions.h"
#include <functional>

class HW {
public:
        virtual bool Init() = 0;
        virtual bool I2CWrite(t_i2cdevices device, uint8_t* wbuffer, int wlength, bool stop) = 0;
        virtual bool I2CRead(t_i2cdevices device, uint8_t* wbuffer, int wlength, uint8_t* rbuffer, int rlength, bool stop) = 0;
        virtual bool I2CRead(t_i2cdevices device, uint8_t* rbuffer, int rlength, bool stop) = 0;
        virtual bool PWMSet(hw_pwm id, float value) = 0;
        virtual bool IOSet(hw_gpio id, bool value) = 0;
        virtual bool IOGet(hw_gpio id, bool* value) = 0;
        virtual void __delay_blocking_ms(uint32_t ms) = 0;
        virtual void PrintDebugConsole(String s) = 0;
        virtual void PrintLineDebugConsole(String s) = 0;
        virtual void Tick() = 0;
        virtual uint64_t GetMillis() = 0;
        virtual int64_t Get_dT_millis(uint64_t ms) = 0;
        virtual bool DataAvailableOnUART0() = 0;
        virtual String ReadUART0UntilEOL() = 0;
        virtual bool WriteUART0(String s) = 0;
        virtual void GetPowerStatus(bool* batteryPowered, float* charge) = 0;
        virtual float GetPIN() = 0;
        virtual float GetBoardTemperature() = 0;
        virtual uint16_t GetSupervisorAlarms() = 0;
};

#endif

//                  #     # ###
//                  ##    #  #
//                  # #   #  #
//                  #  #  #  #
//                  #   # #  #
//                  #    ##  #
//                  #     # ###
//
// Nuclear Instruments 2020 - All rights reserved
// Any commercial use of this code is forbidden
// Contact info@nuclearinstruments.eu

```


