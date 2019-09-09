
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef I2C_IPASS_HPP
#define I2C_IPASS_HPP

/// @file

#include "hwlib.hpp"

class i2c_ipass {
private:
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;

public:

    /// \brief
    /// Constructor for an i2c_ipass object
    /// \details
    /// Example: i2c_ipass i2c_ipass_obect(i2c_bus);
    /// This object requires an hwlib::i2c_bus_bit_banged_scl_sda object
    i2c_ipass(const hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus);
    
    /// \brief
    /// Writes an uint8_t variable to a register from the given module.
    /// \details
    /// Example: i2c_ipass_object.write(0x2D, 0x53, 8);
    ///
    /// This function uses the hwlib::i2c_write_transaction and expects 3 uint8_t variables.
    /// The device id of the module you want to write to.
    /// The register address that you want your data to be writen to on the module.
    /// And the byte you want to write to that register.
    void write(const uint8_t & register_address, const uint8_t & device_id, const uint8_t & data);
    
    /// \brief
    /// Reads and returns an uint8_t variable from the given module.
    /// \details
    /// Example: i2c_ipass_object.write(0x2D, 0x53);
    ///
    /// This function uses the hwlib::i2c_read_transaction and the hwlib::i2c_write_transaction and expects 2 uint8_t variables.
    /// The device id of the module you want to read from.
    /// And the register address that you want to read from.
    /// It returns a uint8_t variable.
    uint8_t read(const uint8_t & register_address, const uint8_t & device_id);
    
};

#endif
