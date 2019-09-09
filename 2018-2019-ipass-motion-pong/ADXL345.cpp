
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "ADXL345.hpp"
#include "registers.hpp"
#include "i2c_ipass.hpp"


ADXL345::ADXL345(const hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus, const uint8_t & device_id, const int & x_offset, const int & y_offset, const int & z_offset):
        i2c_ipass(i2c_bus),
        device_id(device_id),
        x_offset(x_offset),
        y_offset(y_offset),
        z_offset(z_offset)
    {}


void ADXL345::setup(const bool & start_in_measure_mode){
    write(OFSX, device_id, x_offset);
    write(OFSY, device_id, y_offset);
    write(OFSZ, device_id, z_offset);
    if(start_in_measure_mode){
        write(POWER_CTL, device_id, 8);
    }
}


void ADXL345::set_measuring_mode(){
    write(POWER_CTL, device_id, 8);
}


void ADXL345::set_standby_mode(){
    uint8_t old_byte = read(POWER_CTL, device_id);
    uint8_t new_byte = (old_byte & 247);
    write(POWER_CTL, device_id, new_byte);
}


int16_t ADXL345::read_axis_raw(const uint8_t & axis_register_address_1, const uint8_t & axis_register_address_2){
    auto byte_0 = read(axis_register_address_1, device_id);
    auto byte_1 = read(axis_register_address_2, device_id);
    int16_t byte = ( byte_0 | byte_1 << 8);
    return byte;
}


int ADXL345::read_axis_2g(const uint8_t & axis_register_address_1, const uint8_t & axis_register_address_2){
    auto byte_0 = read(axis_register_address_1, device_id);
    auto byte_1 = read(axis_register_address_2, device_id);
    int16_t byte = ( byte_0 | byte_1 << 8);
    auto return_data = (byte * 100) / 256;
    return return_data;
}


int* ADXL345::read_all_axis_2g(int axis_data[3]){
    axis_data[0] = read_axis_2g(DATAX0,DATAX1);
    axis_data[1] = read_axis_2g(DATAY0,DATAY1);
    axis_data[2] = read_axis_2g(DATAZ0,DATAZ1);
    return axis_data;
}
