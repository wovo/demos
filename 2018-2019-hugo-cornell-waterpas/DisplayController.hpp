//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"

class DisplayController
{
public:
	DisplayController();

	void updateTemperatureDisplay(int16_t celsius, int16_t fahrenheit, int16_t kelvin);
	void updateWaterDisplay(int16_t rotation);
	void updateRotationDisplay(int16_t X, int16_t Y, int16_t Z);
	void killDisplays();

private:
	// Temperature bus
	hwlib::target::pin_oc _tempSCL;
	hwlib::target::pin_oc _tempSDA;
	hwlib::i2c_bus_bit_banged_scl_sda _tempBus;

	// Water bus
	hwlib::target::pin_oc _waterSCL;
	hwlib::target::pin_oc _waterSDA;
	hwlib::i2c_bus_bit_banged_scl_sda _waterBus;

	// Rotation bus
	hwlib::target::pin_oc _rotationSCL;
	hwlib::target::pin_oc _rotationSDA;
	hwlib::i2c_bus_bit_banged_scl_sda _rotationBus;

	// Displays
	hwlib::glcd_oled _tempDisplay;
	hwlib::glcd_oled _waterDisplay;
	hwlib::glcd_oled _rotationDisplay;

	// Font
	hwlib::font_default_16x16 _font;

	// Texts
	hwlib::terminal_from _tempText;
	hwlib::terminal_from _rotationText;
};