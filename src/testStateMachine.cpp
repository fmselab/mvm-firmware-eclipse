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

using namespace std;

// an alarm is raised
TEST_CASE("Raise PRESSURE_DROP_INHALE Alarm", "[Alarms]") {
	AlarmClass alarm;
	HAL myHAL;
	t_SystemStatus sys_c;
	myHAL.Init();
	alarm.Init(&myHAL, &sys_c);
	alarm.TriggerAlarm(PRESSURE_DROP_INHALE);
	alarm.Tick();
	// TODO add the check
}

