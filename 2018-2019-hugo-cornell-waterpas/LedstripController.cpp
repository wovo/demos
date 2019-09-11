//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "LedstripController.hpp"

LedstripController::LedstripController() :
	_spiClock(hwlib::target::pins::d7),
	_spiData(hwlib::target::pins::d6),
	_spiBus(_spiClock, _spiData, hwlib::pin_in_dummy),
	_wsChip(_spiBus)
{
	
}

void LedstripController::update(int16_t rotation)
{
	// Correct sensor rotation
	if (rotation > 85) { rotation = 90; }

	// Reset led colors
	for (unsigned int i = 0; i < _activeLedAmount; i++)
	{
		_ledColors[i] = Color(0, 0, 255);
	}

	// Color pattern selection
	if (rotation > 3) // Right side
	{
		// Color index
		if (_colorIndex == _activeLedAmount - 1) { _colorIndex = 0; }
		else { _colorIndex++; }

		// Red
		_ledColors[_colorIndex] = Color(255, 0, 0);

		// Checking rotation
		static bool flashOn = true;
		if (rotation > 70) // Full RED
		{
			_selectedLed = 14;
			for (unsigned int i = 0; i < _activeLedAmount; i++) { _ledColors[i] = Color(255 * flashOn, 0, 0); }
			flashOn = !flashOn;
		}
		else // Direction RED
		{
			_selectedLed = 7 + (rotation / 10);
		}
	}
	else if (rotation < -3) // Left side
	{
		// Color index
		if (_colorIndex == 0) { _colorIndex = _activeLedAmount - 1; }
		else { _colorIndex--; }

		// Red
		_ledColors[_colorIndex] = Color(255, 0, 0);

		// Checking rotation
		static bool flashOn = true;
		if (rotation < -70) // Full RED
		{
			_selectedLed = 0;
			for (unsigned int i = 0; i < _activeLedAmount; i++) { _ledColors[i] = Color(255 * flashOn, 0, 0); }
			flashOn = !flashOn;
		}
		else // Direction RED
		{
			_selectedLed = 7 - abs(rotation / 10);
		}
	}
	else // No rotation
	{
		// Middle
		_selectedLed = 7;

		// LED "kitt"
		static bool goingRight = true;
		if (goingRight)
		{
			if (_colorIndex == _activeLedAmount - 1) { goingRight = false; _colorIndex--; }
			else { _colorIndex++; }
		}
		else
		{
			if (_colorIndex == 0) { goingRight = true; _colorIndex++; }
			else { _colorIndex--; }
		}

		_ledColors[_colorIndex] = Color(0, 255, 0); // Green
	}

	// Led-strip control
	_wsChip.setLedstripColor(0, 0, 0);
	for (size_t i = 0; i < _activeLedAmount; i++)
	{
		_wsChip.setLedColor(_selectedLed + i, _ledColors[i].r, _ledColors[i].g, _ledColors[i].b);
	}
	_wsChip.flush();
}

void LedstripController::killLedstrip()
{
	_wsChip.setLedstripColor(0, 0, 0);
	_wsChip.flush();
}