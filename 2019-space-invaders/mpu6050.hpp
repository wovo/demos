// ===================================================================
//
// File             : mpu6050.hpp
// Part of          : Spaceinvaders application using MPU6050 library
// MPU6050 Library  : https://github.com/theblindmick/MPU6050
// Copyright        : mickbos@hotmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ===================================================================


#ifndef MPU6050_HPP
#define MPU6050_HPP


#include "hwlib.hpp"

struct sensordata {
public:
    sensordata(int16_t x, int16_t y, int16_t z):
        x(x),
        y(y),
        z(z)
    {}

    int16_t x;  //Sensor X axle
    int16_t y;  //sensor Y axle
    int16_t z;  //Sensor Z axle

    /// \brief
    /// Hwlib::cout << operator
    /// /details
    /// hwlib::cout << operator to use with struct sensordata
    friend hwlib::ostream & operator<<(hwlib::ostream & lhs, const sensordata & rhs){
      return lhs 
         << "[" 
         << rhs.x 
         << "/" 
         << rhs.y
         << "/"
         << rhs.z
         << "]";

    };

    bool operator==(const sensordata & rhs) const{
        return (x == rhs.x) && (y==rhs.y) && (z == rhs.z);
    }
};

class sensor {
private:

    int8_t range_gyro = 0;
    int8_t range_accel = 0;
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;
    uint8_t chip_address;
    
public:
    /// \brief
    /// Constructor for sensor use
    /// \details
    /// Constructor to use sensor with. Doesn't need chip address if chipaddress = 0x68 \n
    /// Automatically inits the sensor when instance is made
    sensor(hwlib::i2c_bus_bit_banged_scl_sda i2c_bus, uint8_t chip_address = 0x68):
        i2c_bus(i2c_bus),
        chip_address(chip_address)
    {init();}

    
    
    /// \brief
    /// Writes 8 bits to register_address
    /// \details
    /// Writes the 8 bits from write_value, to register_address
    void write(uint8_t register_address, uint8_t write_value);

    /// \brief
    /// Reads 8 bits from register_address
    /// \details
    /// Reads the 8 bits / byte from register_address
    uint8_t read8(uint8_t regiser_address);
        
    /// \brief
    /// Reads 16 bits from register_address_high and register_address_low
    /// \details
    /// Reads 16 bits by first reading register_address_high and shifting it 8 times
    /// Then reading register_address_low
    int16_t read16(uint8_t register_address_high, uint8_t register_address_low);


    /// \brief
    /// Initiates everything needed to start use
    /// \details
    /// Initiates the use of the MPU6050 by waking it up, checking if there is a MPU6050 connected
    /// and running setup()
    void init();

    /// \brief
    /// Wakes up the MPU6050
    /// \details
    /// Wakes up the MPU6050 by resetting the Power Management Register
    void wakeup();
    
    /// \brief
    /// Returns a 1 if a MPU6050 is connected
    /// \details
    /// Reads the byte in register 0x75 which returns the MPU default address
    /// returns 1 if the register input is the same as the default address
    bool connected();


    /// \brief
    /// Command to setup the 4 set command above
    /// \details
    /// Command to run setGyroConfig(), setAccelConfig(),
    /// setFSync(), setDLPF() and setSampleRate()
    void setup();

    /// \brief
    /// Sets the gyro config
    /// \details 
    /// Sets the full scale range of the gyroscope to around
    /// 250 degrees per second
    void setGyroConfig(uint8_t range);

    /// \brief
    /// Sets the accelerometer config
    /// \details
    /// Sets the full scale range of the accelerometer to around
    /// 19,62 m/s2
    void setAccelConfig(uint8_t range);
   
    /// \brief
    /// Sets the Frame Synchronization
    /// \details
    /// Sets the Frame Synchronization to Input Disabled
    void setFSync(uint8_t FSync);
    
    /// \brief
    /// Sets the Digital Low Pass Filter
    /// \details
    /// Sets the Digital Low Pass Filter to accelerometer 0ms and 260hz bandwidth
    /// and gyroscope 0.98 ms and 256hz bandwidth
    void setDLPF(uint8_t DLPF);
  
    /// \brief 
    /// Sets the Sample rate
    /// \details
    /// Sets the Sample rate to the SampleRate
    void setSampleRate(uint8_t SampleRate);

  
    /// \brief
    /// Reads all the Gyroscope values of all axles
    /// \details
    /// Reads all the axles of the Gyroscope in degrees per second with returnvalue sensordata
    /// which is basically a 3 value array with operator<<
    sensordata readGyro();
   
    /// \brief
    /// Reads all the Accelerometer values of all axles
    /// \details
    /// Reads all the axles of the Accelerometer in m/s2 with returnvalue sensordata
    /// which is basically a 3 value array with operator<<
    sensordata readAccel();
  
    /// \brief
    /// Reads the temperature
    /// \details
    /// Reads the temperature in degrees celsius
    float readTemp();

    /// \brief
    /// Sets the FIFO buffer according to bool enable
    /// \details
    /// Sets the 6th bit of the USER_CONFIG register on or off according
    /// to bool enable to turn on or off the FIFO buffer
    void setFIFO(bool enable);

    /// \brief
    /// Sets if the x axle value gets written to the FIFO buffer
    /// \details
    /// If enable is 1, sets the FIFO Enable register bit to 1
    /// to set all the gyro x axle values to the FIFO buffer
    void setFIFOGyroX(bool enable);

    /// \brief
    /// Sets if the y axle value gets written to the FIFO buffer
    /// \details
    /// If enable is 1, sets the FIFO Enable register bit to 1
    /// to set all the gyro y axle values to the FIFO buffer
    void setFIFOGyroY(bool enable);

    /// \brief
    /// Sets if the z axle value gets written to the FIFO buffer
    /// \details
    /// If enable is 1, sets the FIFO Enable register bit to 1
    /// to set all the gyro z axle values to the FIFO buffer
    void setFIFOGyroZ(bool enable);

    /// \brief
    /// Sets if the temp value gets written to the FIFO buffer
    /// \details
    /// If enable is 1, sets the FIFO Enable register bit to 1
    /// to set all the temperature values to the FIFO buffer
    void setFIFOTemp(bool enable);

    /// \brief
    /// Sets if the Accel values gets written to the FIFO buffer
    /// \details
    /// If enable is 1, sets the FIFO Enable register bit to 1
    /// to set all the accelerometer values to the FIFO buffer
    void setFIFOAccel(bool enable);

    /// \brief
    /// Reads the FIFO counter
    /// \details
    /// Reads the 2 registers that count the amount of data in the FIFO buffer
    uint16_t readFIFOCount();

    /// \brief
    /// Sets the FIFO Overflow interrupt
    /// \Detail
    /// Sets if the FIFO can generate an interrupt when buffer is full
    void setFIFOOflowint(bool enable);

    /// \brief
    /// returns if overflow interrupt is true
    /// \details
    /// Reads the interrupt register and returns the FIFO overflow
    /// Bit status
    bool FIFOOverflow();

    /// \brief
    /// resets the MPU6050
    /// \details
    /// Resets the whole device to factory standards/
    void masterReset();

    /// \brief
    /// Reads the FIFO
    /// \details
    /// Reads the FIFO as long as there is a sample ready
    void readFIFO();
};

#endif // MPU6050_HPP