//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "WS2801.hpp"

class LedstripController
{
public:
	LedstripController();

	void update(int16_t rotation);
	void killLedstrip();

private:
	hwlib::target::pin_out _spiClock;
	hwlib::target::pin_out _spiData;
	hwlib::spi_bus_bit_banged_sclk_mosi_miso _spiBus;

	unsigned int _selectedLed     = 7;
	unsigned int _colorIndex      = 0;
	unsigned int _activeLedAmount = 6;
	std::array<Color, 7> _ledColors;

	WS2801 <20> _wsChip;
};