#define BOOST_TEST_MODULE My Test

#undef  HARDWARE_TARGET_PLATFORM_V3
#undef  HARDWARE_TARGET_PLATFORM_V4

#include <boost/test/included/unit_test.hpp>
#include "MVMCore.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "scaledtime.h"

using namespace std;

enum state {INHALE, EXHALE};

BOOST_AUTO_TEST_SUITE( test_suite )

BOOST_AUTO_TEST_CASE(test_set_parameters) {
	MVMCore mvm;
	// set a right parameter
	BOOST_TEST(mvm.SetParameter("rate","6"), "rate set");
	BOOST_TEST("6", mvm.GetParameter("rate"));
	// set wrong paramters
	BOOST_TEST(! mvm.SetParameter("notexisting","6"),"setting not exiting parameter should return false");
	BOOST_REQUIRE_EQUAL("6", mvm.GetParameter("rate")); // no change
	BOOST_TEST(! mvm.SetParameter("rate","invalidvalue"),"setting not exiting parameter should return false");
	BOOST_REQUIRE_EQUAL("6", mvm.GetParameter("rate")); // no change
}

BOOST_AUTO_TEST_CASE(first_test) {

	MVMCore mvm;
	cout << "init the machine" << std::endl;
	mvm.Init();
	std::cout << mvm.GetParameter("all").c_str() << std::endl;

	mvm.SetParameter("rate","5"); // 12 seconds each
	mvm.SetParameter("ratio","0.5");//I:E=1:2: I: 4 E: 8
	mvm.SetParameter("run", "1");
	long startcycle = getScaledMillisecfromInit();

	//BOOST_CHECK_EQUAL("",mvm.GetParameter("bpm"));
	cout << "pPatient, Flux" << ",last_O2" << ",last_bpm" << ",TidalVolume"
			<< "last_peep" << "GasTemperature" << ",batteryPowered"
			<< "currentBatteryCharge" << "currentP_Peak"
			<< "currentTvIsnp*1000.0" << ",currentTvEsp * 1000.0"
			<< "currentVM"<< std::endl;
	state supposedState = INHALE;
	state lastState = supposedState;
	for (int i = 0; i <= 100; i++) {
		mvm.Tick();
		// every 12 seconds a new cycle starts
		long timefromStartCycle = (startcycle - getScaledMillisecfromInit()) % (12 * 1000);
		// the first 4 secs
		state supposedState = ( 0 <= timefromStartCycle && timefromStartCycle < 4 * 1000) ? INHALE : EXHALE;
		if (lastState != supposedState) {
			cout<< supposedState;
			lastState = supposedState;
		}
		// wait 0.02 seconds
		scaledSleep(20);
	}
}
BOOST_AUTO_TEST_SUITE_END()
