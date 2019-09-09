#ifndef MPU6050_HPP
#define MPU6050_HPP

///@file

#include "hwlib.hpp"

class mpu6050{
private:
    hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus;
    uint8_t adress;
    int16_t read_from_adress(uint8_t adressByte);
    uint8_t scale_range_accel;
public: 
    ///\brief
    ///constructor
    ///\details
    ///this is the constructor for a mpu6050. if no adress is specified, it uses the adress with the last bit as a zero
    ///which means the AD0 pin should be connected to the ground
    ///the chip will be in sleep mode when constructed, to disable sleep, see disableSleep()
    mpu6050(hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus, uint8_t adress = 0x68);
    
    ///\brief
    ///change the range of the accelometer
    ///\details
    ///this function will change the range of the acceleromter. the default value is 0
    ///value has to be within 0-3. it will make the measurment more or less accurate
    void accel_config(uint8_t value);

    ///\brief
    ///return the output of all registers
    ///\details
    ///this function starts an infinity loop which will format the data of the accelerometer x, y, z , gyroscope x, y, z 
    ///and the temperature in celcius, kelvin and fahrenheit and print it
    void return_formatted_data();
    
    ///\brief
    ///put the chip out of sleep mode
    ///\details
    ///this function will put the mpu6050 out of sleep mode
    ///sleep mode has to be disabled to get reliable data from the accelerometer/gyroscope
    void disableSleep();
    
    ///\brief
    ///put the chip in sleep mode
    ///\details
    ///this function puts the chip back in sleep mode. it can be useful if you aren't planning on using the chip anytime soon
    ///if disabled, the gyroscope and accelerometer returns 0, and the temperature sensor returns 36 but is unreliable
    void enableSleep();
    
    ///\brief
    ///put the chip in sleep mode and keep last data
    ///\details
    ///this will put the chip in sleep mode but it won't reset it's registers, which means they will keep the last measurement
    ///until sleep mode is disabled again
    void freeze();
    
    ///\brief
    ///get the x position
    ///\details
    ///get the angle of the x-axis of the current position of a mpu6050 in degrees
    ///it can vary between -90 and 90 degrees
    ///it will be 0 degrees when it is laying, and 90 degrees when it is standing
    int8_t get_position_x();
    
    ///\brief 
    ///get the y position
    ///\details
    ///get the angle of the y-axis of the current position of a mpu6050 in degrees
    ///it can vary between -90 and 90 degrees
    ///it will be 0 degrees when it is laying, and 90 degrees when it is standing
    int8_t get_position_y();
    
    ///\brief
    ///get the z position
    ///\details
    ///get the angle of the z-axis of the current position of a mpu6050 in degrees
    ///it can vary between -90 and 90 degrees
    int8_t get_position_z();
    
    ///\brief
    ///get the current temperature in degrees Celcius
    ///\details
    ///this function will return the current temperature of the chip and surroundings in degrees Celcius
    ///if sleep mode is not disabled, it will return 36 degrees, but it shouldn't be trusted
    int16_t get_temperature_in_C();
    
    ///\brief
    ///get the current temperature in degrees Kelvin
    ///\details
    ///this function will return the current temperature of the chip and surroundings in degrees Kelvin
    ///if sleep mode is not disabled, it will return 309 degrees, but it shouldn't be trusted
    int16_t get_temperature_in_K();
    
    ///\brief
    ///get the current temperature in degrees Fahrenheit
    ///\details
    ///this function will return the current temperature of the chip and surroundings in degrees Fahrenheit
    ///if sleep mode is not disabled, it will return 96 degrees, but it shouldn't be trusted
    int16_t get_temperature_in_F();
    
    ///\brief
    ///get the value from the x-axis from the gyroscope
    ///\details
    ///this function will return the raw value from the x-axis of the gyroscope
    int get_gyro_x();
    
    ///\brief
    ///get the value from the y-axis from the gyroscope
    ///\details
    ///this function will return the raw value from the y-axis of the gyroscope
    int get_gyro_y();
    
    ///\brief
    ///get the value from the z-axis from the gyroscope
    ///\details
    ///this function will return the raw value from the z-axis of the gyroscope
    int get_gyro_z();
        
        
};


#endif //MPU6050_HPP