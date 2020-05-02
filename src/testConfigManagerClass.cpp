/**
 *
 * @brief unit tests for the MVMCore class
 *
 * @author Angelo Gargantini
 */
#undef  HARDWARE_TARGET_PLATFORM_V3
#undef  HARDWARE_TARGET_PLATFORM_V4

#include "MVMCore.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "scaledtime.h"
#include "catch.hpp"

using namespace std;

// a free form test name and, optionally, one or more tags
// TODO use teh real CMC
TEST_CASE( "MVM_set_parameters_test()","[CMC]") {
	MVMCore mvm;
	mvm.Init();
	HAL MVM_HAL;
	// set a right parameter
	REQUIRE(mvm.SetParameter("rate","6"));// "rate set");
	REQUIRE(mvm.GetParameter("rate") == "6");
	// set wrong parameters
	REQUIRE(! mvm.SetParameter("notexisting","6"));//,"setting not exiting parameter should return false");
	REQUIRE(mvm.GetParameter("rate")== "6"); // no change
	REQUIRE(! mvm.SetParameter("rate","invalidvalue"));//,"setting not exiting parameter should return false");
	REQUIRE(mvm.GetParameter("rate") == "6"); // no change
}
