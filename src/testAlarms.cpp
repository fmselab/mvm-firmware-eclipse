/**
 *
 * @brief unit tests for the Alarm class
 *
 * @author Angelo Gargantini
 */

#undef  HARDWARE_TARGET_PLATFORM_V3
#undef  HARDWARE_TARGET_PLATFORM_V4

#include "scaledtime.h"
#include "Alarms.h"
//#include "catch.hpp"
#include <iostream>
#include "HAL.h"

using namespace std;

// an alarm is raised
//TEST_CASE( "Alarms" ) {
int main(int argc, char **argv) {
	AlarmClass alarm;
	HAL myHAL;
	t_SystemStatus sys_c;
	myHAL.Init();
	alarm.Init(&myHAL, &sys_c);
	alarm.TriggerAlarm(PRESSURE_DROP_INHALE);
	alarm.Tick();
}

