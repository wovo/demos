//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "ChipI2C.hpp"

ChipI2C::ChipI2C(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint8_t chipAddress) :
	_i2cBus(bus),
	_chipAddress(chipAddress)
{

}

void ChipI2C::_selectRegister(uint8_t registerAddress)
{
	hwlib::i2c_write_transaction(_i2cBus, _chipAddress).write(registerAddress); // Write transaction with address
}

void ChipI2C::writeToRegister(uint8_t registerAddress, uint8_t value)
{
	const uint8_t content[2] = { registerAddress, value };
	hwlib::i2c_write_transaction(_i2cBus, _chipAddress).write(content, 2); // Write transaction with address and value
}

uint_fast8_t ChipI2C::readRegister(uint8_t registerAddress)
{
	_selectRegister(registerAddress);
	return hwlib::i2c_read_transaction(_i2cBus, _chipAddress).read_byte(); // Read transaction with address
}

uint16_t ChipI2C::mergeBytes(uint8_t MSB, uint8_t LSB)
{
	uint16_t result = 0;
	result = (MSB << 8) | LSB; // Shifting most significant byte into the left byte of uint16_t
	return result;
}