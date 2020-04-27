#define BOOST_TEST_MODULE My Test

#undef  HARDWARE_TARGET_PLATFORM_V3
#undef  HARDWARE_TARGET_PLATFORM_V4

#include <boost/test/included/unit_test.hpp>
#include "MVMCore.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

BOOST_AUTO_TEST_CASE(first_test) {

	MVMCore mvm;
	cout << "init the machine" << std::endl;
	mvm.Init();
	std::cout << mvm.GetParameter("all").c_str() << std::endl;

	mvm.SetParameter("rate","6");
	mvm.SetParameter("run", "1");

	this_thread::sleep_for(chrono::milliseconds(100));
	//BOOST_CHECK_EQUAL("",mvm.GetParameter("bpm"));
	cout << "pPatient, Flux" << ",last_O2" << ",last_bpm" << ",TidalVolume"
			<< "last_peep" << "GasTemperature" << ",batteryPowered"
			<< "currentBatteryCharge" << "currentP_Peak"
			<< "currentTvIsnp*1000.0" << ",currentTvEsp * 1000.0"
			<< "currentVM"<< std::endl;
	for (int i = 0; i <= 100; i++) {
		mvm.Tick();
		// wait 2 seconds
		this_thread::sleep_for(chrono::milliseconds(2000));
		std::cout << mvm.GetParameter("all").c_str() <<  std::endl;
	}
}
