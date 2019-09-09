// Copyright Daniel Bulkowski van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

/// @file

#include "mpu6050.hpp"

// Turns on sensor
void mpu6050::activate(){
    uint8_t data[] = {PWR_MGMT_1, 0};
    bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
    // hwlib::cout << "Sensor has succesfully been turned on! \n";
};

// Sets sensitivity values
void mpu6050::setSensitivity(const uint8_t & accelSens, const uint8_t & gyroSens){
    uint8_t setA[] = {ACCEL_CONFIG, accelSens};
    bus.write(address).write(setA, sizeof(setA) / sizeof(uint8_t));

    uint8_t setG[] = {GYRO_CONFIG, gyroSens};
    bus.write(address).write(setG, sizeof(setG) / sizeof(uint8_t));

    // Get sensitivity from sensor
    uint8_t data[] = {ACCEL_CONFIG};
    bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
    bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));
    int temp = data[0];

    // Translate data to sensitivity and save it to corresponding variable
    if(temp == 0){
        accelSensitivity = 16384;
    } else if(temp == 1){
        accelSensitivity = 8192;
    } else if(temp == 2){
        accelSensitivity = 4096;
    } else if(temp == 3){
        accelSensitivity = 2048;
    }

    // Repeat for gyroscope
    uint8_t data2[] = {GYRO_CONFIG};
    bus.write(address).write(data2, sizeof(data2) / sizeof(uint8_t));
    bus.read(address).read(data2, sizeof(data2) / sizeof(uint8_t));
    int temp2 = data2[0];

    if(temp2 == 0){
        gyroSensitivity = 131;
    } else if(temp2 == 1){
        gyroSensitivity = 65.5;
    } else if(temp2 == 2){
        gyroSensitivity = 32.8;
    } else if(temp2 == 3){
        gyroSensitivity = 16.4;
    }

    // hwlib::cout << "\naccelSensitivity: " << accelSensitivity << "\n" <<
    //             "gyroSensitivity: " << gyroSensitivity;

    // The temperature sensor does not require you to set a sensitivity
};

int16_t mpu6050::getAccelX(){
    // Read first byte of requested data
    uint8_t data[] = {ACCEL_XOUT_H};
    bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
    bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

    // Read second byte of requested data
    uint8_t data2[] = {ACCEL_XOUT_L};
    bus.write(address).write(data2, sizeof(data2) / sizeof(uint8_t));
    bus.read(address).read(data2, sizeof(data2) / sizeof(uint8_t));

    // Calculate, save and return the requested data
    accelX = (data[0] << 8) + data2[0];
    accelX /= accelSensitivity;
    accelX -= accelXCalibration;
    
    return accelX;
};

int16_t mpu6050::getAccelY(){
    // Read first byte of requested data
    uint8_t data[] = {ACCEL_YOUT_H};
    bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
    bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

    // Read second byte of requested data
    uint8_t data2[] = {ACCEL_YOUT_L};
    bus.write(address).write(data2, sizeof(data2) / sizeof(uint8_t));
    bus.read(address).read(data2, sizeof(data2) / sizeof(uint8_t));

    // Calculate, save and return the requested data
    accelY = (data[0] << 8) + data2[0];
    accelY /= accelSensitivity;
    accelY -= accelYCalibration;
    
    return accelY;
};

int16_t mpu6050::getAccelZ(){
    // Read first byte of requested data
    uint8_t data[] = {ACCEL_ZOUT_H};
    bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
    bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

    // Read second byte of requested data
    uint8_t data2[] = {ACCEL_ZOUT_L};
    bus.write(address).write(data2, sizeof(data2) / sizeof(uint8_t));
    bus.read(address).read(data2, sizeof(data2) / sizeof(uint8_t));

    // Calculate, save and return the requested data
    accelZ = (data[0] << 8) + data2[0];
    accelZ /= accelSensitivity;
    accelZ -= accelZCalibration;
    
    return accelZ;
};

int16_t mpu6050::getGyroX(){
    // Read first byte of requested data
    uint8_t data[] = {GYRO_XOUT_H};
    bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
    bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

    // Read second byte of requested data
    uint8_t data2[] = {GYRO_XOUT_L};
    bus.write(address).write(data2, sizeof(data2) / sizeof(uint8_t));
    bus.read(address).read(data2, sizeof(data2) / sizeof(uint8_t));

    // Calculate, save and return the requested data
    gyroX = (data[0] << 8) + data2[0];
    gyroX /= gyroSensitivity;
    gyroX -= gyroXCalibration;
    
    return gyroX;
};

int16_t mpu6050::getGyroY(){
    // Read first byte of requested data
    uint8_t data[] = {GYRO_YOUT_H};
    bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
    bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

    // Read second byte of requested data
    uint8_t data2[] = {GYRO_YOUT_L};
    bus.write(address).write(data2, sizeof(data2) / sizeof(uint8_t));
    bus.read(address).read(data2, sizeof(data2) / sizeof(uint8_t));

    // Calculate, save and return the requested data
    gyroY = (data[0] << 8) + data2[0];
    gyroY /= gyroSensitivity;
    gyroY -= gyroXCalibration;
    
    return gyroY;
};

int16_t mpu6050::getGyroZ(){
    // Read first byte of requested data
    uint8_t data[] = {GYRO_ZOUT_H};
    bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
    bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

    // Read second byte of requested data
    uint8_t data2[] = {GYRO_ZOUT_L};
    bus.write(address).write(data2, sizeof(data2) / sizeof(uint8_t));
    bus.read(address).read(data2, sizeof(data2) / sizeof(uint8_t));

    // Calculate, save and return the requested data
    gyroZ = (data[0] << 8) + data2[0];
    gyroZ /= gyroSensitivity;
    gyroZ -= gyroXCalibration;
    
    return gyroZ;
};

int16_t mpu6050::getTemp(){
    // Read first byte of requested data
    uint8_t data[] = {TEMP_OUT_H};
    bus.write(address).write(data, sizeof(data) / sizeof(uint8_t));
    bus.read(address).read(data, sizeof(data) / sizeof(uint8_t));

    // Read second byte of requested data
    uint8_t data2[] = {TEMP_OUT_L};
    bus.write(address).write(data2, sizeof(data2) / sizeof(uint8_t));
    bus.read(address).read(data2, sizeof(data2) / sizeof(uint8_t));

    // Save, calculate and return the requested data
    temperature = (data[0] << 8) + data2[0];
    temperature /= 340;
    temperature += 36.53;
    
    return temperature;
};

void mpu6050::calibrate(){
    // Take measurements and record them as standards to which other measurements
    // should be held
    accelXCalibration = getAccelX();
    accelYCalibration = getAccelY();
    accelZCalibration = getAccelZ();
    // hwlib::cout << "\naccelXCalibration: " << accelXCalibration <<
    //             "\naccelYCalibration: " << accelYCalibration <<
    //             "\naccelZCalibration: " << accelZCalibration;

    gyroXCalibration = getGyroX();
    gyroYCalibration = getGyroY();
    gyroZCalibration = getGyroZ();
    // hwlib::cout << "\ngyroXCalibration: " << gyroXCalibration <<
    //             "\ngyroYCalibration: " << gyroYCalibration <<
    //             "\ngyroZCalibration: " << gyroZCalibration;
};