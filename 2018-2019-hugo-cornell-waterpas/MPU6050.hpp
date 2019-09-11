//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include "hwlib.hpp"
#include "ChipI2C.hpp"

/// @file

/// \brief
/// Class for MPU6050 chip
/// \details
/// This class serves as a library for the Invensense MPU6050 chip.
/// This chip has several features, for example:
/// - Accelerometer
/// - Gyroscope
/// - Temperature sensor
/// The class is a subclass of ChipI2C, which covers all the I2C stuff.
/// This class has an abstract interface for all of the sensors of the MPU6050.
class MPU6050 : ChipI2C
{
public:
	/// \brief
	/// MPU6050 constructor
	/// \details
	/// This class needs an I2C bus to pass to the I2C class and an accelerometer interval.
	/// The accelerometer interval makes sure the accelerometer outputs are always between
	/// the negative interval and positive interval. Example: values between -90 and 90.
	/// This is useful to display the rotation in degrees for example.
	MPU6050(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint16_t accInterval);
	
	/// \brief
	/// Function to check connection
	/// \details
	/// This function checks if the MPU6050 is successfully connected.
	/// It compares the chip address with the address the chip returns.
	/// Example: if(isConnected()) print("Connection successful");
	virtual bool isConnected();

	/// \brief
	/// Function to print acc values
	/// \details
	/// This function prints the measured accelerometer values of the X, Y and Z dimensions.
	virtual void printAccRotation();

	/// \brief
	/// Function to print gyro values
	/// \details
	/// This function prints the measured gyroscope values of the X, Y and Z dimensions.
	virtual void printGyroRotation();

	/// \brief
	/// Function to print temp values
	/// \details
	/// This function prints the measured temperature sensor values in:
	/// - Celsius
	/// - Fahrenheit
	/// - Kelvin
	virtual void printTemperature();

	/// \brief
	/// Function returning acc X rotation
	/// \details
	/// This function returns the measured accelerometer rotation of the X dimension.
	/// It also converts the rotation to the interval given in the constructor.
	/// Return type is int16_t, because the value has a maximum of ~16384, which is higher than 255 (1 byte).
	virtual const int16_t getAccRotationX();

	/// \brief
	/// Function returning acc Y rotation
	/// \details
	/// This function returns the measured accelerometer rotation of the Y dimension.
	/// It also converts the rotation to the interval given in the constructor.
	/// Return type is int16_t, because the value has a maximum of ~16384, which is higher than 255 (1 byte).
	virtual const int16_t getAccRotationY();

	/// \brief
	/// Function returning acc Z rotation
	/// \details
	/// This function returns the measured accelerometer rotation of the Z dimension.
	/// It also converts the rotation to the interval given in the constructor.
	/// Return type is int16_t, because the value has a maximum of ~16384, which is higher than 255 (1 byte).
	virtual const int16_t getAccRotationZ();

	/// \brief
	/// Function returning gyro X rotation
	/// \details
	/// This function returns the measured gyroscope rotation of the X dimension.
	/// Return type is int16_t, because the value has a maximum of ~50k, which is higher than 255 (1 byte).
	virtual const int16_t getGyroRotationX();

	/// \brief
	/// Function returning gyro Y rotation
	/// \details
	/// This function returns the measured gyroscope rotation of the Y dimension.
	/// Return type is int16_t, because the value has a maximum of ~50k, which is higher than 255 (1 byte).
	virtual const int16_t getGyroRotationY();

	/// \brief
	/// Function returning gyro Z rotation
	/// \details
	/// This function returns the measured gyroscope rotation of the Z dimension.
	/// Return type is int16_t, because the value has a maximum of ~50k, which is higher than 255 (1 byte).
	virtual const int16_t getGyroRotationZ();

	/// \brief
	/// Function returning C temperature
	/// \details
	/// This function returns the measured temperature in Celsius
	/// It converts the temperature from raw values to Celsius.
	virtual const int16_t getTemperatureCelsius();

	/// \brief
	/// Function returning F temperature
	/// \details
	/// This function returns the measured temperature in Fahrenheit
	/// It converts the temperature from Celsius to Fahrenheit.
	virtual const int16_t getTemperatureFahrenheit();

	/// \brief
	/// Function returning K temperature
	/// \details
	/// This function returns the measured temperature in Kelvin.
	/// It converts the temperature from Celsius to Kelvin.
	virtual const int16_t getTemperatureKelvin();

private:
	/// \brief
	/// Function to disable power management
	/// \details
	/// This function disables the power management of the chip.
	/// This is needed because otherwise the chip will go to
	/// a "sleep" mode automatically, which you don't want.
	void _killPowerManagement();

	/// \brief
	/// Function returning acc rotation
	/// \details
	/// This function returns the raw measured accelerometer values.
	const int16_t _getAccRotation(uint8_t msbAddress, uint8_t lsbAddress);

	/// \brief
	/// Function returning gyro rotation
	/// \details
	/// This function returns the raw measured gyroscope values.
	const int16_t _getGyroRotation(uint8_t msbAddress, uint8_t lsbAddress);

	/// \brief
	/// Function returning temperature
	/// \details
	/// This function returns the raw measured temperatre values.
	const int16_t _getTemperature();

	// Variables
	uint16_t _accInterval;
};