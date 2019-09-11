//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include "hwlib.hpp"

 /// @file

 /// \brief
/// Struct for RGB color
/// \details
/// The Color struct serves as an ADT for an RGB (red, green, blue) color.
/// The datatype of the color values is an unsigned int with 8 bits (0-255).
struct Color
{
	Color() = default;
	Color(uint8_t r, uint8_t g, uint8_t b) :
		r(r), g(g), b(b) {  }

	uint8_t r;
	uint8_t g;
	uint8_t b;
	
	bool initialized = false;
};

/// @file
/// \brief
/// Class for WS2801 ledstrip
/// \details
/// This class serves as an interface for the WorldSemi WS2801 RGB ledstrip.
/// Using a template call, you give the amount of LEDs in the ledstrip you want to use.
/// Then you can set the color of an LED (with an index) using the function "setLedColor()".
/// By default all LED colors are 0 (which is no light at all). You can also change the color
/// of the whole ledstrip using the function "setLedstripColor()".
/// The class inherits from hwlib::port_out, because it needs to send bytes through an SPI bus.
/// The idea of inheriting from hwlib::port_out was "stolen" from the hwlib::HC595 class.
template<size_t ledCount>
class WS2801 : public hwlib::port_out
{
public:
	
	/// \brief
	/// WS2801 constructor
	/// \details
	/// This class needs a SPI bus to communicate with the chip.
	/// You also need to specify the amount of LEDs in the connected ledstrip.
	/// Example: WS2801<25> wsChip = WS2801<25>(ledstripBus); <--- Using 25 LEDs
	WS2801(hwlib::spi_bus & bus) :
		_bus(bus)
	{
		hwlib::wait_ms(500);
		_connected = true;
		
		// Set color to 0 by default
		for (size_t i = 0; i < ledCount; i++)
		{
			_ledstripData[i].r = 0x0;
			_ledstripData[i].g = 0x0;
			_ledstripData[i].b = 0x0;
			_ledstripData[i].initialized = true;
		}
	}
	
	/// \brief
	/// Function to set the color of a single LED
	/// \details
	/// This function sets the RGB color of a single LED using an index (starting with 0).
	/// Example: setLedColor(0, 255, 0, 0); <--- sets the first LED to color RED.
	virtual bool setLedColor(const size_t index, const uint8_t red, const uint8_t green, const uint8_t blue)
	{
		// Check if index out of range
		if (index >= ledCount)
		{
			return false; // Return error
		}

		// Change color
		_ledstripData[index].r = red;
		_ledstripData[index].g = green;
		_ledstripData[index].b = blue;

		return true; // Return no error
	}

	/// \brief
	/// Function to set the color of the whole ledstrip
	/// \details
	/// This function sets the RGB colors of all the leds on the ledstrip.
	/// Example: setLedstripColor(0, 255, 0); <--- sets all LEDs to color BLUE.
	virtual void setLedstripColor(const uint8_t red, const uint8_t green, const uint8_t blue)
	{
		for (auto & led : _ledstripData)
		{
			led.r = red;
			led.g = green;
			led.b = blue;
		}
	}
	
	/// \brief
	/// Function to get the current LED color
	/// \details
	/// This function returns the current LED color of a certain LED index.
	/// Example: getLedColor(9); <--- Get LED color of 10th LED in the ledstrip.
	const Color getLedColor(const unsigned int index)
	{
		if (index >= ledCount)
		{
			return Color();
		}

		return _ledstripData[index];
	}

	/// \brief
	/// Function to update ledstrip
	/// \details
	/// This function "flushes" all set LED colors to the WS2801 chip
	/// This function should be called every time you change the LED colors.
	/// Example: "change some LED colors" flush();
	void flush() override 
	{
		for (auto & led : _ledstripData)
		{
			uint8_t fRed   = static_cast<float>(led.r) * 0.4f;
			uint8_t fGreen = static_cast<float>(led.g) * 0.4f;
			uint8_t fBlue  = static_cast<float>(led.b) * 1.0f;
			_bus.transaction(hwlib::pin_out_dummy).write(fRed);
			_bus.transaction(hwlib::pin_out_dummy).write(fGreen);
			_bus.transaction(hwlib::pin_out_dummy).write(fBlue);
		}
	}

	/// \brief
	/// Function to get amount of LEDs
	/// \details
	/// Function returning amount of specified LEDS on the ledstrip.
	/// Example: auto ledCount = getLedAmount();
	virtual inline const size_t getLedAmount()
	{
		return ledCount;
	}

	/// \brief
	/// Function to check chip connection
	/// \details
	/// This function checks if the WS2801 is connected and all the LEDs are turned off (color 0, 0, 0).
	virtual inline const bool isConnected()
	{
		return _connected;
	}
	
private:
	hwlib::spi_bus & _bus; // SPI bus

	std::array<Color, ledCount> _ledstripData; // Array of all LED colors

	bool _connected = false; // Connection variable

	void write(uint_fast16_t x) override {  } // Not used

	uint_fast8_t number_of_pins() override { return 1; } // Not used
};