
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef ADXL345_HPP
#define ADXL345_HPP

/// @file

#include "hwlib.hpp"
#include "i2c_ipass.hpp"

class ADXL345 : public i2c_ipass {
private:
    uint8_t device_id;
    int x_offset;
    int y_offset;
    int z_offset;
    bool start_in_measure_mode;
    
public:

    /// \brief
    /// This is the constructor for an ADXL345 object
    /// \details
    /// Example: ADXL345 accelerometer(i2c_bus, 0x53, -5, 4, 8, 1);
    ///
    /// The first variable is an hwlib::i2c_bus_bit_banged_scl_sda object.
    /// The second variable is the uint8_t device_id of the sensor
    /// The third variable is an int for the x_offset register
    /// The fourth variable is an int for the y_offset register
    /// The fifth variable is an int for the z_offset register
    /// Those variables are used to calibrate the sensor in the setup function
    ADXL345(const hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus, const uint8_t & device_id, const int & x_offset, const int & y_offset, const int & z_offset);
    
    
    /// \brief
    /// This function writes the offset data to the offset registers and can put the sensor in measure mode base on the start_in_measure_mode varible.
    /// \details
    /// Example: ADXL345_object.setup();
    ///
    /// The offset variable and the start_in_measure_mode are stored inside the object itsels so there is no need to give them to the function as variable.
    /// It writes the offset variable to the correct register so that the sensor is calibrated correctly whenever this function is called.
    /// And if set_in_measure_mode is true it also executes the set_measuring_mode function to put the device straight into measure mode.
    void setup(const bool & start_in_measure_mode);
    
    /// \brief
    /// This function wrytes a byte(00001000) to the POWER_CTL register to put the sensor in measure mode by making bit D3 high.
    /// \details
    /// Example: ADXL345_object.set_measuring_mode();
    ///
    /// There is no need to give it any variable since this function will always turn on the same bit in the same register.
    /// You can also skip this function and use the i2c_ipass write directly by using i2c_ipass.write(POWER_CTL, device_id, 8);
    void set_measuring_mode();
    
    /// \brief
    /// This function sets the sensor back in standby mode by clearing bit D3 in the POWER_CTL register
    /// \details
    /// Example: ADXL345_object.set_standby_mode();
    ///
    /// It requires no variable since it always clears the same bit.
    ///
    /// This function only wants to set bit D3 low
    /// So in order to not touch any of the other bits it reads the current data from the register.
    /// It then ands that with 11110111 ensuring that the that aren't D3 and are set stay set.
    void set_standby_mode();
    
    /// \brief
    /// The data for the axis are stored in 2 registers, this function reads both and returns that data.
    /// \details
    /// Example read_axis_2g(DATAX0,DATAX1);
    ///
    /// Since the data for the axis are stored in 2 registers the function requires them both as variable.
    /// Both are const uint8_t variable.
    /// It returns an int16-t variable which contains the combined data from the 2 registers.
    int16_t read_axis_raw(const uint8_t & axis_register_address_1, const uint8_t & axis_register_address_2);
    
    /// \brief
    /// This function does the same as the read_axis_raw function but converts the data to -+2g.
    /// \details
    /// Since the data for the axis are stored in 2 registers the function requires them both as variable.
    /// Both are const uint8_t variable.
    /// It returns an intvariable which contains the combined data from the 2 registers but is also converted to -+2g.
    /// 
    /// Hwlib cannot print floats therefore the data has been multiplied with 100 so that instead of -1.00 to 1.00 we have -100 to 100.
    int read_axis_2g(const uint8_t & axis_register_address_1, const uint8_t & axis_register_address_2);
    
    /// \brief
    /// This function reads all 3 axis and returns an array containing the data from all 3 axis.
    /// \details
    /// Example: int axis_data[3];
    /// Example: ADXL345.read_all_axis_2g(axis_data);
    ///
    /// This function requires an int array that is 3 long.
    /// It reads the 3 axis data and puts it in the array and returns that array.
    /// Do keep in mind that this function uses the read_axis_2g function and not the raw data version.
    int* read_all_axis_2g(int axis_data[3]);
};

#endif
