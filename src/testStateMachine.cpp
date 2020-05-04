/**
 *
 * @brief unit tests for the test machine
 *
 * @author Angelo Gargantini
 */

#include "scaledtime.h"
#include "Alarms.h"
#include "catch.hpp"
#include <iostream>
#include "HAL.h"
#include "MVM_StateMachine.h"

using namespace std;

// an alarm is raised
TEST_CASE("State machine in the PCV mode", "[StateMachine]") {
	MVM_StateMachine MVM_SM;
	AlarmClass alarm;
	HAL MVM_HAL;
	t_SystemStatus sys_c;
	ConfigManagerClass CMC;

	// init
	MVM_HAL.Init();
	CMC.Init(NULL, &sys_c, &alarm);
	//CMC.addHandler_AfterConfigurationSet(std::bind(&MVMCore::ConfigurationChanged_Event, this));
	MVM_HAL.SetInputValve(0);
	MVM_HAL.SetOutputValve(0);
	MVM_HAL.SetAlarmLed(false);
	MVM_HAL.SetAlarmRele(false);
	MVM_HAL.SetBuzzer(false);
//	MVM_HAL.addHandler_PLoop(std::bind(&MVMCore::PLoop_Event, this));
//	MVM_HAL.addHandler_PPatient(std::bind(&MVMCore::PPatient_Event, this));
//	MVM_HAL.addHandler_FlowSens(std::bind(&MVMCore::FlowIn_Event, this));
//	MVM_HAL.addHandler_FlowVenturi(std::bind(&MVMCore::FlowVenturi_Event, this));
//	MVM_HAL.addHandler_HardwareAlarm(std::bind(&MVMCore::HardwareAlarm_Event, this, _1));
//	MVM_SM.addHandler_NewCycle(std::bind(&MVMCore::NewCycle_Event, this));
//	MVM_SM.addHandler_Exhale(std::bind(&MVMCore::Exhale_Event, this));
//	MVM_SM.addHandler_EndCycle(std::bind(&MVMCore::EndCycle_Event, this));
//
//	MEM_Ppatient_LP = new CircularBuffer(10);
//	old_delta_ppatient = 0;

	sys_c.pPatient = 0;
	sys_c.pLoop = 0;
	sys_c.FlowIn = 0;

	sys_c.batteryPowered = false;
	sys_c.currentBatteryCharge = 100;
	sys_c.in_over_pressure_emergency = false;

	// init
	alarm.Init(&MVM_HAL, &sys_c);
	MVM_SM.Init(&MVM_HAL, &alarm, &CMC.core_config, &sys_c, 10);
	// check some initial values
	CHECK_FALSE(CMC.core_config.pause_inhale);
	// TODO complete the checking
	// start testing the machine
	for(int i = 0; i < 100; i ++){
		MVM_SM.Tick();
		scaledSleep(20);
	}
	// now run it
	MVM_HAL.dbg.SetVerboseLevel(DBG_ALL);
	CHECK(CMC.SetParameter("rate", "5"));
	CHECK(CMC.SetParameter("ratio", "0.5")); //I:E=1 --> ratio = 0.5 (see excel ratio = I/(I+E)) I:6  E: 6
	cout<< " inhale_ms " << CMC.core_config.inhale_ms << endl; // check 6 seconds
	cout<< " exhale_ms " << CMC.core_config.exhale_ms << endl;
	// set to PSV
	CMC.core_config.BreathMode = M_BREATH_ASSISTED;
	CMC.core_config.run = true;
	cout<< " start running " << endl;
	for(int i = 0; i < 1000; i ++){
		MVM_SM.Tick();
		//scaledSleep(20);
	}
}

