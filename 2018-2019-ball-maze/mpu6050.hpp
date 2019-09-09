// ===========================================================================
//
// Copyright Noah Titarsole (noah.titarsole@student.hu.nl) 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)
//
// ===========================================================================

#ifndef MPU_6050
#define MPU_6050

#include "hwlib.hpp"

/// @file

/// \brief
/// MPU-6050 library
/// \details
/// In this library you can find functions to read the output from the MPU-6050.
class mpu6050{
private:

   //MPU-6050 registers
   static constexpr const uint8_t CONFIG       = 0x1A;
   static constexpr const uint8_t GYRO_CONFIG  = 0x1B;
   static constexpr const uint8_t ACCEL_CONFIG = 0x1C;

   static constexpr const uint8_t ACCEL_XOUT_H = 0x3B;
   static constexpr const uint8_t ACCEL_XOUT_L = 0x3C;
   static constexpr const uint8_t ACCEL_YOUT_H = 0x3D;
   static constexpr const uint8_t ACCEL_YOUT_L = 0x3E;
   static constexpr const uint8_t ACCEL_ZOUT_H = 0x3F;
   static constexpr const uint8_t ACCEL_ZOUT_L = 0x40;

   static constexpr const uint8_t TEMP_OUT_H   = 0x41;
   static constexpr const uint8_t TEMP_OUT_L   = 0x42;

   static constexpr const uint8_t GYRO_XOUT_H  = 0x43;
   static constexpr const uint8_t GYRO_XOUT_L  = 0x44;
   static constexpr const uint8_t GYRO_YOUT_H  = 0x45;
   static constexpr const uint8_t GYRO_YOUT_L  = 0x46;
   static constexpr const uint8_t GYRO_ZOUT_H  = 0x47;
   static constexpr const uint8_t GYRO_ZOUT_L  = 0x48;

   static constexpr const uint8_t USER_CTRL    = 0x6A;
   static constexpr const uint8_t PWR_MGMT_1   = 0x6B;


   // I2C
   hwlib::i2c_bus & bus; 
   uint_fast8_t address;

   // Accelerator
   int16_t accel_x;
   int16_t accel_y;
   int16_t accel_z;

   int accel_base_x = 0;
   int accel_base_y = 0;
   int accel_base_z = 0;

   int accel_s = 16384;

   // Gyroscope
   int16_t gyro_x;
   int16_t gyro_y;
   int16_t gyro_z;

   int gyro_base_x = 0;
   int gyro_base_y = 0;
   int gyro_base_z = 0;
   
   float gyro_s = 131.0;

   // Temperature
   int16_t temperature;

   public:

   /// \brief
   /// MPU-6050 constructor
   /// \details
   /// Receives the bus and the address.
   mpu6050(hwlib::i2c_bus & bus, uint_fast8_t address = 0x68):
      bus(bus),
      address(address)
   {}

   /// \brief
   /// Turn MPU-6050 on
   /// \details
   /// Turns the sensor on.
   void power_on();

   /// \brief
   /// Gets sensor sensitivity setting
   /// \details
   /// Receives the accelerator sensitivity setting and the gyroscope sensitivity setting.
   void get_sens_values(uint8_t AFS_SEL, uint8_t FS_SEL);

   /// \brief
   /// Sets sensor sensitivity
   /// \details
   /// Takes the accelerator sensitivity setting and the gyroscope sensitivity setting from the registers.
   /// It converts the values from the registers to sensitivity.
   void set_sens_values();

   /// \brief
   /// Calibrate sensor
   /// \details
   /// Reads the accelerator and gyroscope to set the base values.
   void calibrate();

   /// \brief
   /// initialize sensor
   /// \details
   /// Receives the accelerator sensitivity setting and the gyroscope sensitivity setting, then calls 4 functions,
   void initialize(uint8_t AFS_SEL, uint8_t FS_SEL);

   /// \brief
   /// Gets accelerator x-axis
   /// \details
   /// Reads the x-axis value and returns it after converting it.
   int16_t get_accel_x();

   /// \brief
   /// Gets accelerator y-axis
   /// \details
   /// Reads the y-axis value and returns it after converting it.
   int16_t get_accel_y();

   /// \brief
   /// Gets accelerator z-axis
   /// \details
   /// Reads the z-axis value and returns it after converting it.
   int16_t get_accel_z();

   /// \brief
   /// Gets gyroscope x-axis
   /// \details
   /// Reads the x-axis value and returns it after converting it.
   int16_t get_gyro_x();

   /// \brief
   /// Gets gyroscope y-axis
   /// \details
   /// Reads the y-axis value and returns it after converting it.
   int16_t get_gyro_y();

   /// \brief
   /// Gets gyroscope z-axis
   /// \details
   /// Reads the z-axis value and returns it after converting it.
   int16_t get_gyro_z();

   /// \brief
   /// Gets temperature
   /// \details
   /// Reads the temperature value and returns it after converting it to degrees celsius.
   int16_t get_temp();
};

#endif //MPU_6050