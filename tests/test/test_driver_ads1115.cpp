#include <arduino.h>
#include <driver_ADS1115.h>

#include <catch.hpp>
#include <catch2/trompeloeil.hpp>

SCENARIO("ADS1115 ADC", "[driver][ads1115]") {
  GIVEN("Test") {
    ADC_ADS1115 sensor;
    DriverContext dc;

    MockHW hw;
    DebugIfaceClass dbg;

    dbg.Init(DBG_NONE, &hw);

    dc.hwi = &hw;
    dc.dbg = &dbg;

    WHEN("Init is called and all commands succeed") {

      bool res = sensor.Init(IIC_ADC_0, &dc);
      THEN("Init is successful") { REQUIRE(res == true); }
    }
  }
}
