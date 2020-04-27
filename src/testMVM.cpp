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
	cout << mvm.GetParameter("all") <<std::endl;
	mvm.SetParameter("run", "1");
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << "data " << mvm.GetParameter("all") <<std::endl;
/*	//BOOST_CHECK_EQUAL("",mvm.GetParameter("bpm"));
	cout << "test data\n";
	cout << mvm.GetParameter("all")<<std::endl;
	mvm.Tick();
	cout << mvm.GetParameter("all")<<std::endl;
	mvm.Tick();
	cout << mvm.GetParameter("all")<<std::endl;
	mvm.Tick();
	cout << mvm.GetParameter("all")<<std::endl;
	mvm.Tick();
	cout << mvm.GetParameter("all")<<std::endl;
	mvm.Tick();
	// now start a run
	mvm.SetParameter("run", "1");
	cout << mvm.GetParameter("all")<<std::endl;
	mvm.Tick();*/
}
