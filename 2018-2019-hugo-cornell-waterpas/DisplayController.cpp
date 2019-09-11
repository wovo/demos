//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "DisplayController.hpp"

DisplayController::DisplayController() :

	// Temperature bus
	_tempSCL(hwlib::target::pins::d19),
	_tempSDA(hwlib::target::pins::d18),
	_tempBus(_tempSCL, _tempSDA),
	
	// Water bus
	_waterSCL(hwlib::target::pins::d17),
	_waterSDA(hwlib::target::pins::d16),
	_waterBus(_waterSCL, _waterSDA),

	// Rotation bus
	_rotationSCL(hwlib::target::pins::d15),
	_rotationSDA(hwlib::target::pins::d14),
	_rotationBus(_rotationSCL, _rotationSDA),

	// Displays
	_tempDisplay(_tempBus, 0x3c),
	_waterDisplay(_waterBus, 0x3c),
	_rotationDisplay(_rotationBus, 0x3c),

	// Texts
	_font(),
	_tempText(_tempDisplay, _font),
	_rotationText(_rotationDisplay, _font)
{
	
}

void DisplayController::updateTemperatureDisplay(int16_t celsius, int16_t fahrenheit, int16_t kelvin)
{
	// Clear display
	_tempDisplay.clear();
	
	// Draw
	_tempText << "\f--Temp--\nC:" << celsius << "\nF:" << fahrenheit << "\nK:" << kelvin << hwlib::flush;
}

void DisplayController::updateWaterDisplay(int16_t rotation)
{
	// Clear display
	_waterDisplay.clear();

	// Display horizontal waterdrop lines
	for (uint16_t x = 0; x < _waterDisplay.size.x; x++)
	{
		_waterDisplay.write(hwlib::xy(x, 10));
		_waterDisplay.write(hwlib::xy(x, _waterDisplay.size.y - 2));
	}

	// Display vertical waterdrop lines
	for (uint16_t y = 10; y < _waterDisplay.size.y - 2; y++)
	{
		_waterDisplay.write(hwlib::xy(43, y));
		_waterDisplay.write(hwlib::xy(84, y));
	}

	// Display water drop
	auto width = _waterDisplay.size.x;
	auto xMiddle = width / 2;
	auto offset = rotation;

	// Upper half
	for (uint16_t y = 1; y < 40; y++)
	{
		for (uint16_t x = xMiddle - y / 2; x < xMiddle + y / 2; x++)
		{
			_waterDisplay.write(hwlib::xy(offset + x, 10 + y));
		}
	}

	// Lower half
	uint16_t decreaser = 1;
	uint16_t y = 39;
	uint16_t cycles = 0;
	for (uint16_t idk = 39; idk > 10; idk -= decreaser)
	{
		if ((cycles % 5) == 0) decreaser++;
		cycles++;
		y++;
		for (uint16_t x = xMiddle - idk / 2; x < xMiddle + idk / 2; x++)
		{
			_waterDisplay.write(hwlib::xy(offset + x, 10 + y));
		}
	}

	_waterDisplay.flush();
}

void DisplayController::updateRotationDisplay(int16_t X, int16_t Y, int16_t Z)
{
	// Clear display
	_rotationDisplay.clear();

	// Draw
	_rotationText << "\fRotation\nX:" << X << "\nY:" << Y << "\nZ:" << Z << hwlib::flush;
}

void DisplayController::killDisplays()
{
	_waterDisplay.clear();
	_rotationDisplay.clear();
	_tempDisplay.clear();
	_waterDisplay.flush();
	_rotationDisplay.flush();
	_tempDisplay.flush();
}
