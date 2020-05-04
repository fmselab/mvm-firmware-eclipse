#include <arduino.h>
#include <driver_5525DSO.h>

#include <catch.hpp>
#include <catch2/trompeloeil.hpp>

SCENARIO("MS5525DSO Pressure Sensor Tests", "[driver][ms5525dso]") {
  GIVEN("Test") {
    Sensor5525DSO sensor;
    DriverContext dc;

    MockHW hw;
    DebugIfaceClass dbg;

    dbg.Init(DBG_NONE, &hw);

    dc.hwi = &hw;
    dc.dbg = &dbg;

    WHEN("Init is called and all commands succeed") {
      REQUIRE_CALL(hw, I2CWrite(ANY(t_i2cdevices), ANY(unsigned char*),
                                ANY(int), ANY(bool)))
          .RETURN(true);
      REQUIRE_CALL(hw, __delay_blocking_ms(100));
      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices), ANY(unsigned char*), ANY(int),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .RETURN(true)
          .TIMES(AT_MOST(6));
      REQUIRE_CALL(hw, GetMillis()).RETURN(1ull);
      bool res = sensor.Init(IIC_PS_1, DS_01, OVS_1024, &dc);
      THEN("Init is successful") { REQUIRE(res == true); }
    }
    WHEN("Init is called and I2C write fails") {
      REQUIRE_CALL(hw, I2CWrite(ANY(t_i2cdevices), ANY(unsigned char*),
                                ANY(int), ANY(bool)))
          .RETURN(false);
      REQUIRE_CALL(hw, __delay_blocking_ms(100));
      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices), ANY(unsigned char*), ANY(int),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .RETURN(false)
          .TIMES(AT_MOST(6));
      // REQUIRE_CALL(hw, GetMillis()).RETURN(1ull);
      bool res = sensor.Init(IIC_PS_1, DS_01, OVS_1024, &dc);
      THEN("Init fails") { REQUIRE(res == false); }
    }
    WHEN("Perform measurement") {
      trompeloeil::sequence seq;

      REQUIRE_CALL(hw, I2CWrite(ANY(t_i2cdevices), ANY(unsigned char*),
                                ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .RETURN(true);
      REQUIRE_CALL(hw, __delay_blocking_ms(100)).IN_SEQUENCE(seq);

      // Send out coefficients
      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices), ANY(unsigned char*), ANY(int),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .SIDE_EFFECT(_4[0] = 0x33)
          .SIDE_EFFECT(_4[1] = 0xA8)
          .RETURN(true);
      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices), ANY(unsigned char*), ANY(int),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .SIDE_EFFECT(_4[0] = 0x1B)
          .SIDE_EFFECT(_4[1] = 0xA7)
          .RETURN(true);
      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices), ANY(unsigned char*), ANY(int),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .SIDE_EFFECT(_4[0] = 0x0C)
          .SIDE_EFFECT(_4[1] = 0xC8)
          .RETURN(true);
      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices), ANY(unsigned char*), ANY(int),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .SIDE_EFFECT(_4[0] = 0x06)
          .SIDE_EFFECT(_4[1] = 0x32)
          .RETURN(true);
      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices), ANY(unsigned char*), ANY(int),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .SIDE_EFFECT(_4[0] = 0x98)
          .SIDE_EFFECT(_4[1] = 0xD1)
          .RETURN(true);

      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices), ANY(unsigned char*), ANY(int),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .SIDE_EFFECT(_4[0] = 0x1F)
          .SIDE_EFFECT(_4[1] = 0x65)
          .RETURN(true);

      REQUIRE_CALL(hw, GetMillis()).RETURN(1ull).IN_SEQUENCE(seq);

      // doMeasure mocking
      // Requesting pressure
      REQUIRE_CALL(hw, I2CWrite(ANY(t_i2cdevices), ANY(unsigned char*),
                                ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .RETURN(true);
      REQUIRE_CALL(hw, __delay_blocking_ms(ANY(int))).IN_SEQUENCE(seq);
      REQUIRE_CALL(hw, I2CWrite(ANY(t_i2cdevices), ANY(unsigned char*),
                                ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .RETURN(true);
      REQUIRE_CALL(hw, __delay_blocking_ms(ANY(int))).IN_SEQUENCE(seq);

      // Get pressure reading
      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .SIDE_EFFECT(_2[0] = 0x00)
          .SIDE_EFFECT(_2[1] = 0x00)
          .SIDE_EFFECT(_2[2] = 0x00)
          .RETURN(true);

      // Request temperature reading
      REQUIRE_CALL(hw, I2CWrite(ANY(t_i2cdevices), ANY(unsigned char*),
                                ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .RETURN(true);
      REQUIRE_CALL(hw, __delay_blocking_ms(ANY(int))).IN_SEQUENCE(seq);
      REQUIRE_CALL(hw, I2CWrite(ANY(t_i2cdevices), ANY(unsigned char*),
                                ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .RETURN(true);
      REQUIRE_CALL(hw, __delay_blocking_ms(ANY(int))).IN_SEQUENCE(seq);

      // Get temperature reading
      REQUIRE_CALL(hw, I2CRead(ANY(t_i2cdevices),
                               ANY(unsigned char*), ANY(int), ANY(bool)))
          .IN_SEQUENCE(seq)
          .SIDE_EFFECT(_2[0] = 0x00)
          .SIDE_EFFECT(_2[1] = 0x00)
          .SIDE_EFFECT(_2[2] = 0x00)
          .RETURN(true);

      bool res = sensor.Init(IIC_PS_1, DS_01, OVS_1024, &dc);
      float p;
      float t;
      sensor.doMeasure(&p, &t);

      THEN("Pressure") {
        REQUIRE(p == Approx(-199.492f).margin(0.001f));
        REQUIRE(t == Approx(12.41f).margin(0.001f));
        REQUIRE(res == true);
      }
    }
  }
}
