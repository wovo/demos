//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include "hwlib.hpp"

/// @file
/// \brief
/// Class for I2C chips
/// \details
/// This is a class which communicates with computer chips that support the I2C protocol.
/// It has 3 interface functions: one for writing a byte to a register with a certain address,
/// one for reading a byte from a registeR with a certain address,
/// and one for merging two bytes into one value (uint166t)
class ChipI2C
{
public:
	/// \brief
	/// ChipI2C constructor
	/// \details
	/// The class needs an I2C bus to operate and the address of the chip itself
	ChipI2C(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint8_t chipAddress);

protected:
	/// \brief
	/// Function to write to register
	/// \details
	/// This function writes a byte to the register of the given address.
	/// The writing happens through an I2C write transaction.
	/// Example: writeToRegister(0x1, 0xFF) <--- Write 255 at register 1
	virtual void writeToRegister(uint8_t registerAddress, uint8_t value);
	
	/// \brief
	/// Function to read a register
	/// \details
	/// This function reads a byte from the register of the given address.
	/// The writing happens through an I2C read transaction.
	/// But before it can read, the register of the given address has to be selected first.
	/// Example: auto output = readRegister(0x1) <--- Read 1 byte at register 1
	virtual uint_fast8_t readRegister(uint8_t registerAddress);

	/// \brief
	/// Function to merge two bytes into one value
	/// \details
	/// This function merges two bytes (uint8_t) into one value (uint16_t) using bit shifting.
	/// MSB = Most Significant Bit
	/// LSB = Least Significant Bit
	/// Example:
	/// uint8_t MSB = 0xFF; <--- 11111111
	/// uint8_t LSB = 0x1; <--- 00000001
	/// auto output = mergeBytes(MSB, LSB); <--- New value: 1111111100000001
	virtual uint16_t mergeBytes(uint8_t MSB, uint8_t LSB);
	
private:
	/// \brief
	/// Function to select a register
	/// \details
	/// This function writes the given address to the chip.
	/// This makes sure the register on the given address is "selected".
	/// This is needed when you want to read a byte from a certain register.
	/// Example: _selectRegister(0x1); <--- Used for reading a byte at a certain address.
	void _selectRegister(uint8_t registerAddress);

	hwlib::i2c_bus_bit_banged_scl_sda & _i2cBus; // I2C bus

	uint8_t _chipAddress; // Chip address
};