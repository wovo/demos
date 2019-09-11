//          Copyright Hugo Cornel 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "MPU6050.hpp"

// MPU6050 accelerometer register addresses
#define ACC_X_MSB_ADDRESS   0x3B
#define ACC_X_LSB_ADDRESS   0x3C
#define ACC_Y_MSB_ADDRESS   0x3D
#define ACC_Y_LSB_ADDRESS   0x3E
#define ACC_Z_MSB_ADDRESS   0x3F
#define ACC_Z_LSB_ADDRESS   0x40

// MPU6050 gyroscope register addresses
#define GYRO_X_MSB_ADDRESS  0x43
#define GYRO_X_LSB_ADDRESS  0x44
#define GYRO_Y_MSB_ADDRESS  0x45
#define GYRO_Y_LSB_ADDRESS  0x46
#define GYRO_Z_MSB_ADDRESS  0x47
#define GYRO_Z_LSB_ADDRESS  0x48

// MPU6050 temperaturemeter register addresses
#define TEMP_MSB_ADDRESS    0x41
#define TEMP_LSB_ADDRESS    0x42

// MPU6050 chip address
#define CHIP_ADDRESS        0x68

// MPU6050 "who am I" address
#define WHO_AM_I_ADDRESS    0x75

// MPU6050 power management address
#define POWER_ADDRESS       0x6B

MPU6050::MPU6050(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint16_t accInterval) :
	ChipI2C(bus, CHIP_ADDRESS),
	_accInterval(accInterval)
{
	hwlib::wait_ms(500); // Giving the Arduino extra time to prepare
	_killPowerManagement();
}

bool MPU6050::isConnected()
{
	auto chipAddress = readRegister(WHO_AM_I_ADDRESS);
	
	return (chipAddress == CHIP_ADDRESS);
}

void MPU6050::printAccRotation()
{
	hwlib::cout << "Acc rotation  = " << "X: " << getAccRotationX() << " Y: " << getAccRotationY() << " Z: " << getAccRotationZ() << hwlib::endl;
}

void MPU6050::printGyroRotation()
{
	hwlib::cout << "Gyro rotation = " << "X: " << getGyroRotationX() << " Y: " << getGyroRotationY() << " Z: " << getGyroRotationZ() << hwlib::endl;
}

void MPU6050::printTemperature()
{
	hwlib::cout << "Temperature =   " << "C: " << getTemperatureCelsius() << " F: " << getTemperatureFahrenheit() << " K: " << getTemperatureKelvin() << hwlib::endl;
}

const int16_t MPU6050::getAccRotationX()
{
	return _getAccRotation(ACC_X_MSB_ADDRESS, ACC_X_LSB_ADDRESS);
}

const int16_t MPU6050::getAccRotationY()
{
	return _getAccRotation(ACC_Y_MSB_ADDRESS, ACC_Y_LSB_ADDRESS);
}

const int16_t MPU6050::getAccRotationZ()
{
	return _getAccRotation(ACC_Z_MSB_ADDRESS, ACC_Z_LSB_ADDRESS);
}

const int16_t MPU6050::getGyroRotationX()
{
	return _getGyroRotation(GYRO_Y_MSB_ADDRESS, GYRO_Y_LSB_ADDRESS);
}

const int16_t MPU6050::getGyroRotationY()
{
	return _getGyroRotation(GYRO_X_MSB_ADDRESS, GYRO_X_LSB_ADDRESS);
}

const int16_t MPU6050::getGyroRotationZ()
{
	return _getGyroRotation(GYRO_Z_MSB_ADDRESS, GYRO_Z_LSB_ADDRESS);
}

const int16_t MPU6050::getTemperatureCelsius()
{
	// Converting from raw values to Celsius
	auto result = _getTemperature();
	float floatedResult = float(result);
	floatedResult /= 340.0f;
	floatedResult += 36.53f;
	floatedResult -= 5; // Correction
	result = int16_t(floatedResult);
	return result;
}

const int16_t MPU6050::getTemperatureFahrenheit()
{
	// Converting from Celsius to Fahrenheit
	auto result = getTemperatureCelsius();
	float floatedResult = float(result);
	floatedResult *= 1.8f;
	floatedResult += 32.0f;
	result = int16_t(floatedResult);
	return result;
}

const int16_t MPU6050::getTemperatureKelvin()
{
	// Converting from Celsius to Kelvin
	auto result = getTemperatureCelsius();
	float floatedResult = float(result);
	floatedResult += 273.15f;
	result = int16_t(floatedResult);
	return result;
}

void MPU6050::_killPowerManagement()
{
	writeToRegister(POWER_ADDRESS, 0x0);
}

const int16_t MPU6050::_getAccRotation(uint8_t msbAddress, uint8_t lsbAddress)
{
	// Reading the accelerometer values
	auto x_MSB = readRegister(msbAddress);
	auto x_LSB = readRegister(lsbAddress);
	int16_t result = mergeBytes(x_MSB, x_LSB);
	
	// Converting the range of the measurements to an interval set by the user
	float floatedResult = float(result);
	floatedResult /= 16384.0f;
	floatedResult *= float(_accInterval);	
	result = int16_t(floatedResult);

	// Limiting the rotation angle to 90 degrees (due to inaccurate measurements like 91 or 92 degrees)
	if (result < 0) // Negative limitation
	{
		if (result < -_accInterval)
		{
			result = -_accInterval;
		}
	}
	else // Positive limitation
	{
		if (result > _accInterval)
		{
			result = _accInterval;
		}
	}

	return result;
}

const int16_t MPU6050::_getGyroRotation(uint8_t msbAddress, uint8_t lsbAddress)
{
	// Reading the gyroscope values
	auto x_MSB = readRegister(msbAddress);
	auto x_LSB = readRegister(lsbAddress);
	int16_t result = mergeBytes(x_MSB, x_LSB);
	return result;
}

const int16_t MPU6050::_getTemperature()
{
	// Reading the temperature values
	auto temp_MSB  = readRegister(TEMP_MSB_ADDRESS);
	auto temp_LSB  = readRegister(TEMP_LSB_ADDRESS);
	int16_t result = mergeBytes(temp_MSB, temp_LSB);
	return result;
}