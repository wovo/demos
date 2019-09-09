// ===================================================================
//
// File             : mpu6050.cpp
// Part of          : Spaceinvaders application using MPU6050 library
// MPU6050 Library  : https://github.com/theblindmick/MPU6050
// Copyright        : mickbos@hotmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ===================================================================

#include "mpu6050.hpp"

// Register list
#define REGISTER_SAMPLE_RATE                            0x19
#define REGISTER_CONFIG                                 0x1A
#define REGISTER_CONFIG_GYRO                            0x1B
#define REGISTER_CONFIG_ACCEL                           0x1C
#define REGISTER_FIFO_ENABLE                            0x23
#define REGISTER_INTTERUPT_CONFIG                       0x37
#define REGISTER_INTERRUPT_ENABLE                       0x38
#define REGISTER_INTERRUPT_STATUS                       0x3A
#define REGISTER_ACCEL_XOUT_H                           0x3B
#define REGISTER_ACCEL_XOUT_L                           0x3C
#define REGISTER_ACCEL_YOUT_H                           0x3D
#define REGISTER_ACCEL_YOUT_L                           0x3E
#define REGISTER_ACCEL_ZOUT_H                           0x3F
#define REGISTER_ACCEL_ZOUT_L                           0x40
#define REGISTER_TEMP_OUT_H                             0x41
#define REGISTER_TEMP_OUT_L                             0x42
#define REGISTER_GYRO_XOUT_H                            0x43
#define REGISTER_GYRO_XOUT_L                            0x44
#define REGISTER_GYRO_YOUT_H                            0x45
#define REGISTER_GYRO_YOUT_L                            0x46
#define REGISTER_GYRO_ZOUT_H                            0x47
#define REGISTER_GYRO_ZOUT_L                            0x48
#define REGISTER_I2C_DELAY_CONTROL                      0x67
#define REGISTER_SIGNAL_PATH_RESET                      0x68
#define REGISTER_USER_CONTROL                           0x69
#define REGISTER_POWER_MANAGEMENT                       0x6B
#define REGISTER_WHO_AM_I                               0x75

//Sensor information
#define I2C_DEFAULT_ADDRESS                             0x68

#define GYRO_FACTOR                                     (1.0/131.0)

#define ACCEL_FACTOR                                    (9.81 / 16384.0)

#define TEMP_LINEAR_COEF                                (1.0/340.0)
#define TEMP_OFFSET                                     36.53

void sensor::write(uint8_t register_address, uint8_t write_value){
    hwlib::i2c_write_transaction transaction(sensor::i2c_bus, chip_address);
    transaction.write(register_address);
    transaction.write(write_value);
    transaction.~i2c_write_transaction();
}

uint8_t sensor::read8(uint8_t register_address){
    hwlib::i2c_write_transaction register_transaction(i2c_bus, chip_address);
    register_transaction.write(register_address);
    register_transaction.~i2c_write_transaction();

    hwlib::i2c_read_transaction read_transaction(i2c_bus, chip_address);
    return read_transaction.read_byte();
};

int16_t sensor::read16(uint8_t register_address_high, uint8_t register_address_low){
    return read8(register_address_high)<<8 | read8(register_address_low);
}



void sensor::setGyroConfig(uint8_t range = 0){
    write(REGISTER_CONFIG_GYRO, read8(REGISTER_CONFIG_GYRO) & (0b11100111 + (range<<3)));
};

void sensor::setAccelConfig(uint8_t range = 0){
    write(REGISTER_CONFIG_ACCEL, read8(REGISTER_CONFIG_ACCEL) & (0b11100111 + (range<<3)));
};

void sensor::setFSync(uint8_t FSync = 0){
    write(REGISTER_CONFIG, read8(REGISTER_CONFIG) & (0b11000111 + (FSync<<3)));
};

void sensor::setDLPF(uint8_t DLPF = 0){
    write(REGISTER_CONFIG, read8(REGISTER_CONFIG) & (0b11111000 + (DLPF)));
}

void sensor::setSampleRate(uint8_t SampleRate = 0){
    write(REGISTER_SAMPLE_RATE, SampleRate);
}

void sensor::setup(){
    setAccelConfig();
    setAccelConfig();
    setFSync();
    setDLPF();
    setSampleRate();
};



void sensor::wakeup(){
    write(REGISTER_POWER_MANAGEMENT, 0b00000000);
    hwlib::wait_ms(500);
}

bool sensor::connected(){
    return read8(REGISTER_WHO_AM_I) == I2C_DEFAULT_ADDRESS || read8(REGISTER_WHO_AM_I) == I2C_DEFAULT_ADDRESS + 1;
};

void sensor::init(){
    wakeup();
    
    if(!sensor::connected()){
        hwlib::cout << "not connected";
    }

    setup();
};


sensordata sensor::readGyro(){
    int16_t x = read16(REGISTER_GYRO_XOUT_H, REGISTER_GYRO_XOUT_L) * GYRO_FACTOR;
    int16_t y = read16(REGISTER_GYRO_YOUT_H, REGISTER_GYRO_XOUT_L) * GYRO_FACTOR; 
    int16_t z = read16(REGISTER_GYRO_ZOUT_H, REGISTER_GYRO_ZOUT_L) * GYRO_FACTOR;
    return sensordata(x,y,z);
}

sensordata sensor::readAccel(){
    int16_t x = read16(REGISTER_ACCEL_XOUT_H, REGISTER_ACCEL_XOUT_L) * ACCEL_FACTOR;
    int16_t y = read16(REGISTER_ACCEL_YOUT_H, REGISTER_ACCEL_XOUT_L) * ACCEL_FACTOR;
    int16_t z = read16(REGISTER_ACCEL_ZOUT_H, REGISTER_ACCEL_ZOUT_L) * ACCEL_FACTOR;
    return sensordata(x,y,z);
}

float sensor::readTemp(){
    uint16_t rawTempValue = read16(REGISTER_TEMP_OUT_H, REGISTER_TEMP_OUT_L);
    return rawTempValue * TEMP_LINEAR_COEF + TEMP_OFFSET;
}


void sensor::setFIFO(bool enable){
    if(enable){
        sensor::write(REGISTER_USER_CONTROL, read8(REGISTER_USER_CONTROL) | 0b01000000);
    }
    else{
        sensor::write(REGISTER_USER_CONTROL, read8(REGISTER_USER_CONTROL) & 0b10111111);
    }
}

void sensor::setFIFOGyroX(bool enable){
    if(enable){
        sensor::write(REGISTER_FIFO_ENABLE, read8(REGISTER_FIFO_ENABLE) | 0b01000000);
    }
    else{
        sensor::write(REGISTER_USER_CONTROL, read8(REGISTER_USER_CONTROL) & 0b10111111);
    }
}

void sensor::setFIFOGyroY(bool enable){
    if(enable){
        sensor::write(REGISTER_FIFO_ENABLE, read8(REGISTER_FIFO_ENABLE) | 0b00100000);
    }
    else{
        sensor::write(REGISTER_USER_CONTROL, read8(REGISTER_USER_CONTROL) & 0b11011111);
    }
}

void sensor::setFIFOGyroZ(bool enable){
    if(enable){
        sensor::write(REGISTER_FIFO_ENABLE, read8(REGISTER_FIFO_ENABLE) | 0b00010000);
    }
    else{
        sensor::write(REGISTER_USER_CONTROL, read8(REGISTER_USER_CONTROL) & 0b11101111);
    }
}


void sensor::setFIFOTemp(bool enable){
    if(enable){
        write(REGISTER_FIFO_ENABLE, read8(REGISTER_FIFO_ENABLE) | 0b10000000);
    }
    else{
        write(REGISTER_USER_CONTROL, read8(REGISTER_USER_CONTROL) & 0b01111111);
    }
}

void sensor::setFIFOAccel(bool enable){
    if(enable){
        write(REGISTER_FIFO_ENABLE, read8(REGISTER_FIFO_ENABLE) | 0b00001000);
    }
    else{
        write(REGISTER_USER_CONTROL, read8(REGISTER_USER_CONTROL) & 0b11110111);
    }
}

uint16_t sensor::readFIFOCount(){
    return read16(REGISTER_FIFO_COUNTER_H, REGISTER_FIFO_COUNTER_L);
}

void sensor::setFIFOOflowint(bool enable){
    if(enable){
        write(REGISTER_INTERRUPT_ENABLE, read8(REGISTER_INTERRUPT_ENABLE) | 0b00010000);
    }
    else{
        write(REGISTER_INTERRUPT_ENABLE, read8(REGISTER_INTERRUPT_ENABLE) & 0b11101111);
    }
}

bool sensor::FIFOOverflow(){
    return (read8(REGISTER_INTERRUPT_STATUS)>>4) & true;
}

void sensor::masterReset(){
    write(REGISTER_POWER_MANAGEMENT, 0b10000000);
}

uint8_t sensor::readFIFO(){
    uint16_t samplesinFIFO = read16(REGISTER_FIFO_COUNTER_H, REGISTER_FIFO_COUNTER_L);
    if(samplesinFIFO){
        return read8(REGISTER_FIFO_DATA);
    }
    else{
        return 0;
    }
    
}