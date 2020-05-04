/*
 * H4_fake.cpp
 *
 *  Created on: 1 mag 2020
 *      Author: AngeloGargantini
 */

#include "fw_board_ni_v4.h"

bool HW_V4::Init() {
}
bool HW_V4::I2CWrite(t_i2cdevices device, uint8_t *wbuffer, int wlength, bool stop) {
//	throw std::runtime_error("not implemented!");
}
bool HW_V4::I2CRead(t_i2cdevices device, uint8_t *wbuffer, int wlength,
		uint8_t *rbuffer, int rlength, bool stop) {
//	throw std::runtime_error("not implemented!");
}
bool HW_V4::I2CRead(t_i2cdevices device, uint8_t *rbuffer, int rlength,
		bool stop) {
}
bool HW_V4::PWMSet(hw_pwm id, float value) {
}
bool HW_V4::IOSet(hw_gpio id, bool value) {
}
bool HW_V4::IOGet(hw_gpio id, bool *value) {
}
void HW_V4::__delay_blocking_ms(uint32_t ms) {
}
void HW_V4::PrintDebugConsole(String s) {
	std::cout << s.c_str() << std::endl;
}
void HW_V4::PrintLineDebugConsole(String s) {
	std::cout << s.c_str() << std::endl;
}
void HW_V4::Tick() {
	throw std::runtime_error("HW_V4::Tick not implemented!");
}
uint64_t HW_V4::GetMillis() {
}
int64_t HW_V4::Get_dT_millis(uint64_t ms) {
}
bool HW_V4::DataAvailableOnUART0() {
}
String HW_V4::ReadUART0UntilEOL() {
}
bool HW_V4::WriteUART0(String s) {
}
void HW_V4::GetPowerStatus(bool *batteryPowered, float *charge) {
}
float HW_V4::GetPIN() {
}
float HW_V4::GetBoardTemperature() {
}
uint16_t HW_V4::GetSupervisorAlarms() {
}

