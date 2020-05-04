/*
 * HAL.cpp - a fake HAL
 *
 *  Created on: 26 apr 2020
 *      Author: AngeloGargantini
 */

#include "HAL.h"
#include <chrono>
#include <iostream>
#include <thread>
#include "scaledtime.h"
#include <string>
#include <iomanip>
#include "fw_board_ni_v4.h"

using namespace std;

static HW_V4 myHW;

struct  HAL_Status{
	float InputValve;
	bool OutputValve;
	bool alarmedled, alarmedrel;
	bool buzzer;
	void printstate(char* s){
		std::cout << "[" << fixed<< std::setprecision(1) << getScaledMillisecfromInit()/1000.0 << "] ";
		cout << s << "  -- valves (in,out) (" + std::to_string(InputValve) + "," + std::to_string(OutputValve) + ")" << std::endl;
	}
};


// static to protect
static HAL_Status current_state;

//////////////////

void HAL::Init() {
	startScaledTime();
	hwi.Init();
	dbg.Init(DBG_ALL, &myHW);
	dbg.Init(DBG_WARNING, &hwi);
	_dc.hwi = &myHW;
	_dc.dbg = &dbg;
	std::cout << "init HAL" << std::endl;
}

void HAL::Tick() {
	std::runtime_error("ERROR IN NAVIGATION");
}

float HAL::GetPressureValve(int32_t Delay) {
	// What it is? see limits
	return 10;
}
float HAL::GetPressurePatient(int32_t Delay) {
	// What it is? see limits
	return 10;
}
float HAL::GetFlowInspire(int32_t Delay) {
	return 10;
}
float HAL::GetFlowVenturi(int32_t Delay) {
	return 10;
}
float HAL::GetPVenturi(int32_t Delay) {
	throw std::runtime_error("3not implemented!");
}
void HAL::SetInputValve(float value) {
//	static long startphase = 0;
//	// TODO this should go to the real HAL to avoid double setting the valve output
	if (current_state.InputValve == value) return;
	if (value >0  && current_state.InputValve == 0){
		current_state.InputValve = value;
		// open -> start expiration
		current_state.printstate("start inspiration");
	} else if (value == 0  && current_state.InputValve > 0) {
		current_state.InputValve = value;
		//closed --> end expiration
		current_state.printstate("end inspiration");
	}
	// start new phase
	//startphase = getScaledMillisec();
	//if (value > 0 && current_state.OutputValve)
	//	std::runtime_error("valve both opens");
}

float HAL::GetInputValve() {
	return current_state.InputValve;
}
// true open
void HAL::SetOutputValve(bool value) {
	if (value == current_state.OutputValve) return;
	if (value && !current_state.OutputValve){
		current_state.OutputValve = value;
		// open -> start expiration
		current_state.printstate("start expiration");
	} else if (!value && current_state.OutputValve){
		current_state.OutputValve = value;
		//closed --> end expiration
		current_state.printstate("end expiration");
	}
}
float HAL::GetOutputValve() {
	return current_state.OutputValve;
}
void HAL::SetBuzzer(bool value) {
//	buzzer = value;
}
void HAL::SetAlarmLed(bool value) {
//	alarmedled = value;
}
void HAL::SetAlarmRele(bool value) {
//	alarmedrel = value;
}

float HAL::GetVolumeVenturi() {
	throw std::runtime_error("11 not implemented!");
}
float HAL::GetVolumeInput() {
	throw std::runtime_error("12 not implemented!");
}
void HAL::ResetVolumeVenturi() {
	throw std::runtime_error("13 not implemented!");
}
void HAL::ResetVolumeInput() {
	throw std::runtime_error("14 not implemented!");
}

bool HAL::DataAvailableOnUART0() {
	throw std::runtime_error("15 not implemented!");
}

String HAL::ReadUART0UntilEOL() {
	throw std::runtime_error("16 not implemented!");
}

bool HAL::WriteUART0(String s) {
	throw std::runtime_error("17 not implemented!");
}

void HAL::GetInputValvePID(float *pid_slow, float *pid_fast) {
	//throw std::runtime_error("18 not implemented!");
}

uint64_t HAL::GetMillis() {
	return getScaledMillisec();
}
// used in Alarm
unsigned long millis() {
	return getScaledMillisec();
}

int64_t HAL::Get_dT_millis(uint64_t ms) {
	return (int64_t) (GetMillis() - ms);
}

float HAL::ZeroPressureSensor(t_pressure_sensor ps) {
	return 0;
}

void HAL::SetZeroPressureSensor(t_pressure_sensor ps, float value) {
	throw std::runtime_error("21 not implemented!");
}

void HAL::CorrectZeroPressureSensor(t_pressure_sensor ps, float value) {
	// nothing to do throw std::runtime_error("22 not implemented!");
}
void HAL::ConfigureInputValvePID(float P, float I, float D, float P2, float I2,
		float D2, float pid_limit) {
	//throw std::runtime_error("23 not implemented!");
	// do nothing
}

void HAL::delay_ms(float ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds((int) ms));
}

float HAL::GetOxygen() {
	return 10;
	//throw std::runtime_error("25 not implemented!");
}
void HAL::CalibrateOxygenSensorInAir() {
	throw std::runtime_error("26 not implemented!");
}

void HAL::CalibrateOxygenSensorInPureOxygen() {
	throw std::runtime_error("26 not implemented!");
}

void HAL::TriggerAlarm(t_ALARM alarm_code) {
	throw std::runtime_error("28 not implemented!");
}

float HAL::GetGasTemperature() {
	throw std::runtime_error("29 not implemented!");
}

void HAL::GetPowerStatus(bool *batteryPowered, float *charge) {
	// for now use corrent
	*batteryPowered = false;
}

void HAL::FlushPipes(bool run, float valve) {
	throw std::runtime_error("31 not implemented!");
}

void HAL::DOVenturiMeterScan() {
	throw std::runtime_error("32 not implemented!");
}

