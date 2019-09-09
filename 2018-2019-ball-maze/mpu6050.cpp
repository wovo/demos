// ===========================================================================
//
// Copyright Noah Titarsole (noah.titarsole@student.hu.nl) 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)
//
// ===========================================================================

#include "mpu6050.hpp"

void mpu6050::power_on(){
   uint8_t data[] = {PWR_MGMT_1, 0};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
   // hwlib::cout << "power on\n";
}

void mpu6050::get_sens_values(uint8_t AFS_SEL, uint8_t FS_SEL){
   uint8_t data[] = {ACCEL_CONFIG, AFS_SEL};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));

   uint8_t data_2[] = {GYRO_CONFIG, FS_SEL};
   bus.write(address).write(data_2, sizeof(data_2) / sizeof(uint8_t));
   hwlib::cout << "\nsensor value: " << AFS_SEL << ", " << FS_SEL << '\n';
}

void mpu6050::set_sens_values(){
   hwlib::cout << "sensor base value old: " << accel_s << ", " << int(gyro_s) << '\n';
   uint8_t data[] = {ACCEL_CONFIG};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
   bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));
   int new_accel_s = data[0];
   if(new_accel_s == 0){
      accel_s = 16384;  // +/- 2g
   } else if(new_accel_s == 1){
      accel_s = 8192;   // +/- 4g
   } else if(new_accel_s == 2){
      accel_s = 4096;   // +/- 8g
   } else if(new_accel_s == 3){
      accel_s = 2048;   // +/- 16g
   }
   
   uint8_t data_2[] = {GYRO_CONFIG};
   bus.write(address).write(data_2, sizeof(data_2) / sizeof(uint8_t));
   bus.read(address).read(data, sizeof(data_2) / sizeof(uint8_t));
   int new_gyro_s = data_2[0];
   if(new_gyro_s == 0){
      gyro_s = 131.0;  // +/- 250 degrees/s
   } else if(new_gyro_s == 1){
      gyro_s = 65.5;  // +/- 500 degrees/s
   } else if(new_gyro_s == 2){
      gyro_s = 32.8;  // +/- 1000 degrees/s
   } else if(new_gyro_s == 3){
      gyro_s = 16.4;  // +/- 2000 degrees/s
   }
   hwlib::cout << "sensor base value new: " << accel_s << ", " << int(gyro_s) << '\n';
}

void mpu6050::calibrate(){
   hwlib::cout << "accel base value old: " << accel_base_x << ", " << accel_base_y << ", " << accel_base_z << '\n';
   accel_base_x = get_accel_x();
   accel_base_y = get_accel_y();
   accel_base_z = get_accel_z();
   hwlib::cout << "accel base value new: " << accel_base_x << ", " << accel_base_y << ", " << accel_base_z << '\n';

   hwlib::cout << "gyro base value old: " << gyro_base_x << ", " << gyro_base_y << ", " << gyro_base_z << '\n';
   gyro_base_x = get_gyro_x();
   gyro_base_y = get_gyro_y();
   gyro_base_z = get_gyro_z();
   hwlib::cout << "gyro base value new: " << gyro_base_x << ", " << gyro_base_y << ", " << gyro_base_z << '\n';
}

void mpu6050::initialize(uint8_t AFS_SEL, uint8_t FS_SEL){
   power_on();
   get_sens_values(AFS_SEL, FS_SEL);
   set_sens_values();
   calibrate();
   // hwlib::cout << "initialized\n";
}

int16_t mpu6050::get_accel_x(){
   uint8_t data[] = {ACCEL_XOUT_H};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
   bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

   uint8_t data_2[] = {ACCEL_XOUT_L};
   bus.write(address).write(data_2, sizeof(data_2) / sizeof(uint8_t));
   bus.read(address).read(data_2, sizeof(data_2) / sizeof(uint8_t));

   accel_x = (data[0] << 8) + data_2[0];
   accel_x /= accel_s;
   accel_x -= accel_base_x;
   return accel_x;
}

int16_t mpu6050::get_accel_y(){
   uint8_t data[] = {ACCEL_YOUT_H};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
   bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

   uint8_t data_2[] = {ACCEL_YOUT_L};
   bus.write(address).write(data_2, sizeof(data_2) / sizeof(uint8_t));
   bus.read(address).read(data_2, sizeof(data_2) / sizeof(uint8_t));

   accel_y = (data[0] << 8) + data_2[0];
   accel_y /= accel_s;
   accel_y -= accel_base_y;
   accel_y *= -1;
   return accel_y;
}

int16_t mpu6050::get_accel_z(){
   uint8_t data[] = {ACCEL_ZOUT_H};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
   bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

   uint8_t data_2[] = {ACCEL_ZOUT_L};
   bus.write(address).write(data_2, sizeof(data_2) / sizeof(uint8_t));
   bus.read(address).read(data_2, sizeof(data_2) / sizeof(uint8_t));

   accel_z = (data[0] << 8) + data_2[0];
   accel_z /= accel_s;
   accel_z -= accel_base_z;
   return accel_z;
}

int16_t mpu6050::get_gyro_x(){
   uint8_t data[] = {GYRO_XOUT_H};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
   bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

   uint8_t data_2[] = {GYRO_XOUT_L};
   bus.write(address).write(data_2, sizeof(data_2) / sizeof(uint8_t));
   bus.read(address).read(data_2, sizeof(data_2) / sizeof(uint8_t));

   gyro_x = (data[0] << 8) + data_2[0];
   gyro_x /= gyro_s;
   gyro_x -= gyro_base_x;
   return gyro_x;
}

int16_t mpu6050::get_gyro_y(){
   uint8_t data[] = {GYRO_YOUT_H};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
   bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

   uint8_t data_2[] = {GYRO_YOUT_L};
   bus.write(address).write(data_2, sizeof(data_2) / sizeof(uint8_t));
   bus.read(address).read(data_2, sizeof(data_2) / sizeof(uint8_t));

   gyro_y = (data[0] << 8) + data_2[0];
   gyro_y /= gyro_s;
   gyro_y -= gyro_base_y;
   return gyro_y;
}

int16_t mpu6050::get_gyro_z(){
   uint8_t data[] = {GYRO_ZOUT_H};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
   bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

   uint8_t data_2[] = {GYRO_ZOUT_L};
   bus.write(address).write(data_2, sizeof(data_2) / sizeof(uint8_t));
   bus.read(address).read(data_2, sizeof(data_2) / sizeof(uint8_t));

   gyro_z = (data[0] << 8) + data_2[0];
   gyro_z /= gyro_s;
   gyro_z -= gyro_base_z;
   return gyro_z;
}

int16_t mpu6050::get_temp(){
   uint8_t data[] = {TEMP_OUT_H};
   bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
   bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

   uint8_t data_2[] = {TEMP_OUT_L};
   bus.write(address).write(data_2, sizeof(data_2) / sizeof(uint8_t));
   bus.read(address).read(data_2, sizeof(data_2) / sizeof(uint8_t));

   temperature = (data[0] << 8) + data_2[0];
   temperature = temperature/340 + 36.53; // Formula for temperature in degrees Celsius
   return temperature;
}