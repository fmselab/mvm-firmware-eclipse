#include <arduino.h>
#include <driver_SFM3019.h>

#include <catch.hpp>
#include <catch2/trompeloeil.hpp>

using trompeloeil::_;
using trompeloeil::ge;

SCENARIO("SFM3019 Flow Sensor Tests", "[driver][sfm3019]") {
  GIVEN("Test") {
    SensorSFM3019 sensor;
    DriverContext dc;

    MockHW hw;
    DebugIfaceClass dbg;

    dbg.Init(DBG_NONE, &hw);

    dc.hwi = &hw;
    dc.dbg = &dbg;

    WHEN("Init is called and general reset fails") {
      // General reset
      REQUIRE_CALL(hw, I2CWrite(ANY(t_i2cdevices), ANY(unsigned char*),
                                ANY(int), ANY(bool)))
          .RETURN(false);
      ALLOW_CALL(hw, __delay_blocking_ms(_));
      ALLOW_CALL(arduino_mock, millis()).RETURN(0);

      bool res = sensor.Init(IIC_FLOW1, &dc);
      THEN("Init is successful") { REQUIRE(res == false); }
    }
    WHEN("Init is called and general reset succeeds") {
      // General reset
      REQUIRE_CALL(hw, I2CWrite(ANY(t_i2cdevices), ANY(unsigned char*),
                                ANY(int), ANY(bool)))
          .RETURN(true);
      // Sensirion sleep, bizarrely SFM3019_SOFT_RESET_TIME_US is defined inside
      // .cpp file!
      REQUIRE_CALL(hw, __delay_blocking_ms(ge(8ul)));
      bool res = sensor.Init(IIC_FLOW1, &dc);
      THEN("Init is successful") { REQUIRE(res == false); }
    }
  }
}
