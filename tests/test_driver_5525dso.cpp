#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <catch.hpp>

#include <driver_5525DSO.h>

SCENARIO("MS5525DSO Pressure Sensor Tests", "[driver][ms5525dso]") {

    VenturiFlowMeter fm;

    GIVEN("Model SpiroquantH_R122P04") {
        fm.Init(t_VenturiSensorModel::SpiroquantH_R122P04);
        WHEN("Getting flow") {
            float flow = fm.GetFlow(0.0f, 0.0f);
            THEN("Flow should be equal to something") {
                REQUIRE(flow == Approx(0.0f).margin(0.001f) );
            }
        }
    }
    /*
    GIVEN("Model ALPE_1551") {

    }

    GIVEN("Invalid Model") {

    }
    */
}
