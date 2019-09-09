// Copyright Daniel Bulkowski van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

/// @file

#include "hwlib.hpp"

/// \brief
/// Class for the mpu-6050
/// \details
/// A class created to make use of the mpu-6050, whether you need the 
/// acceleration- or temperature-sensor, or even the gyroscope.
/// The class also includes ways to change the sensor sensitivity and
/// a way to calibrate the sensor before use
class mpu6050{
private:
    // Necessary MPU-6050 registers
    static constexpr const uint8_t USER_CTRL = 0x6A;
    static constexpr const uint8_t PWR_MGMT_1 = 0x6B;

    static constexpr const uint8_t CONFIG = 0x1A;
    static constexpr const uint8_t GYRO_CONFIG = 0x1B;
    static constexpr const uint8_t ACCEL_CONFIG = 0x1C;

    static constexpr const uint8_t ACCEL_XOUT_H = 0x3B;
    static constexpr const uint8_t ACCEL_XOUT_L = 0x3C;
    static constexpr const uint8_t ACCEL_YOUT_H = 0x3D;
    static constexpr const uint8_t ACCEL_YOUT_L = 0x3E;
    static constexpr const uint8_t ACCEL_ZOUT_H = 0x3F;
    static constexpr const uint8_t ACCEL_ZOUT_L = 0x40;

    static constexpr const uint8_t GYRO_XOUT_H = 0x43;
    static constexpr const uint8_t GYRO_XOUT_L = 0x44;
    static constexpr const uint8_t GYRO_YOUT_H = 0x45;
    static constexpr const uint8_t GYRO_YOUT_L = 0x46;
    static constexpr const uint8_t GYRO_ZOUT_H = 0x47;
    static constexpr const uint8_t GYRO_ZOUT_L = 0x48;

    static constexpr const uint8_t TEMP_OUT_H = 0x41;
    static constexpr const uint8_t TEMP_OUT_L = 0x42;

    // I2C connection
    hwlib::i2c_bus & bus;
    uint_fast8_t address;

    // Calibration variables
    int accelXCalibration = 0;
    int accelYCalibration = 0;
    int accelZCalibration = 0;

    int gyroXCalibration = 0;
    int gyroYCalibration = 0;
    int gyroZCalibration = 0;

    // Sensitivity
    int accelSensitivity = 2048;
    float gyroSensitivity = 16.4;

    // Requested data
    int16_t accelX;
    int16_t accelY;
    int16_t accelZ;

    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ;

    int16_t temperature;

public:
    /// \brief
    /// Constructor for the mpu6050 class
    /// \details
    /// The contructor takes a hwlib::i2c_bus variable and an uint_fast8_t variable
    /// which is standard set to 0x68 (which is the address of the mpu-6050)
    mpu6050(hwlib::i2c_bus & bus, uint_fast8_t address = 0x68):
        bus(bus),
        address(address)
    {};

    /// \brief
    /// Turns on the sensor
    /// \details
    /// Sends a signal to the sensor which turns it on
    void activate();

    /// \brief
    /// Sets the desired sensitivity
    /// \details
    /// Sets the desired gyroscope or acceleration-sensor sensitivities and saves them
    void setSensitivity(const uint8_t & accelSens, const uint8_t & gyroSens);

    /// \brief
    /// Returns x-variable of acceleration-sensor
    /// \details
    /// Requests x-variable of accelration-sensor, then divide it by the sensitivity,
    /// subtracts the variables received from calibrating the sensor and 
    /// then returns the x-variable of the acceleration-sensor
    int16_t getAccelX();

    /// \brief
    /// Returns y-variable of acceleration-sensor
    /// \details
    /// Requests y-variable of accelration-sensor, then divide it by the sensitivity,
    /// subtracts the variables received from calibrating the sensor and 
    /// then returns the y-variable of the acceleration-sensor
    int16_t getAccelY();

    /// \brief
    /// Returns z-variable of acceleration-sensor
    /// \details
    /// Requests z-variable of accelration-sensor, then divide it by the sensitivity,
    /// subtracts the variables received from calibrating the sensor and 
    /// then returns the z-variable of the acceleration-sensor
    int16_t getAccelZ();

    /// \brief
    /// Returns x-variable of gyroscope
    /// \details
    /// Requests x-variable of gyroscope, then divide it by the sensitivity,
    /// subtracts the variables received from calibrating the sensor and 
    /// then returns the x-variable of the gyroscope
    int16_t getGyroX();

    /// \brief
    /// Returns y-variable of acceleration-sensor
    /// \details
    /// Requests y-variable of accelration-sensor, then divide it by the sensitivity,
    /// subtracts the variables received from calibrating the sensor and 
    /// then returns the y-variable of the acceleration-sensor
    int16_t getGyroY();

    /// \brief
    /// Returns z-variable of acceleration-sensor
    /// \details
    /// Requests z-variable of accelration-sensor, then divide it by the sensitivity,
    /// subtracts the variables received from calibrating the sensor and 
    /// then returns the z-variable of the acceleration-sensor
    int16_t getGyroZ();

    /// \brief
    /// Returns temperature
    /// \details
    /// Requests temperature from the sensor, divides this number by 340,
    /// adds 36.53 and returns the calculated temperature
    int16_t getTemp();

    /// \brief
    /// Calibrates the sensor
    /// \details
    /// Makes a measurement for all variables except for temperature
    /// Saves these taken measurements as base variables upon which following
    /// variables will be based
    void calibrate();
};