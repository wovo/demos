
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "i2c_ipass.hpp"


i2c_ipass::i2c_ipass(const hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus): i2c_bus(i2c_bus) {}


void i2c_ipass::write(const uint8_t & register_address, const uint8_t & device_id, const uint8_t & data){
    const uint8_t writeBytes[2] = {register_address, data};
    hwlib::i2c_write_transaction(i2c_bus, device_id).write(writeBytes, 2);
}


uint8_t i2c_ipass::read(const uint8_t & register_address, const uint8_t & device_id){
    hwlib::i2c_write_transaction(i2c_bus, device_id).write(register_address);
    uint8_t data = hwlib::i2c_read_transaction(i2c_bus, device_id).read_byte();
    return data;
}
