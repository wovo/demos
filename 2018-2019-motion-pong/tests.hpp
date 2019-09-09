
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef TESTS_HPP
#define TESTS_HPP

/// @file

#include "i2c_ipass.hpp"
#include "ADXL345.hpp"
#include "registers.hpp"

class tests {
private: 
    i2c_ipass i2c_ipass_object;
    ADXL345 ADXL345_object;
    
public:
    /// \brief
    /// Constructor for a tests object.
    /// \details
    /// The constructor requires an i2c_ipass object and an ADXL345_object.
    tests(const i2c_ipass & i2c_ipass_object, const ADXL345 & ADXL345_object);
    
    /// \brief
    /// Tests the read function from the i2c_ipass class.
    /// \details
    /// The 0x00 register from the ADXL345 module holds the device id which is 0xE5 or 229.
    /// By using that value we can check if the data that the read function returns is what's supposed to be in the register.    
    bool test_i2c_ipass_read();
    
    /// \brief
    /// Tests the write function form the i2c_ipass class.
    /// \details
    /// We tested the read function in the previous test so we can use that to check our write function.
    /// For this test the function writes 8 to the z offest register so if we read that register it should containt the value 8.
    /// Daarna zetten we de byte weer op 0 om te voorkomen dat het ergens anders problemen veroorzaakt.
    bool test_i2c_ipass_write();
    
    /// \brief
    /// Tests wether or not the sensor can start measuring
    /// \details
    /// The sensor starts in standby mode and untill it gets into measure mode the axis data is 0.
    /// What this test does is that it first checks wether or not they are 0.
    /// Then if all axis are 0 it uses the setup funciton to calibrate the sensor and put it in measure mode.
    /// The setup function just contains a bunch of i2c_ipass write functions which we already tested.
    /// Once the sensor has entered measure mode it starts to fill the axis registers with data.
    /// Do keep in mind that when the sensor is hold upright the X and Y axis are 0 so in order for this funciton to work the sensor needs to be at an angle.
    bool test_ADXL345_measuring();
    
    /// \brief
    /// Test if the set_standby_mode function can return the sensor to standby mode without touching the other bits in the register.
    /// \details
    /// So the set_stanby_mode function is designed to only clear bit D3 which is the measure mode bit.
    /// To test this we write 12 to the register which is 00001100.
    /// Then after we exectute the set_standby_mode function it should clear bit D3 leaving 00000100 which is 4.
    /// Then it writes 0 to the POWER_CTL register to ensure we don't leave any unwanted bits in there.
    bool test_ADXL345_set_standby_mode();
    
    /// \brief
    /// This function runs all tests and prints the results
    /// \details
    /// Example: tests_oject.print_test_results();
    void print_test_results();
};

#endif
