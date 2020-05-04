/*
// Build fails currently, issues need to be fixed, see ISSUES.md
#include <catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <arduino.h>
#include <MVMCore.h>

TEST_CASE( "MVM_set_parameters_test()","MVM") {
	MVMCore mvm;
	// set a right parameter
	REQUIRE(mvm.SetParameter("rate","6"));// "rate set");
	REQUIRE(mvm.GetParameter("rate") == "6");
	// set wrong parameters
	REQUIRE(! mvm.SetParameter("notexisting","6"));//,"setting not exiting parameter should return false");
	REQUIRE(mvm.GetParameter("rate")== "6"); // no change
	REQUIRE(! mvm.SetParameter("rate","invalidvalue"));//,"setting not exiting parameter should return false");
	REQUIRE(mvm.GetParameter("rate") == "6"); // no change
}
*/
