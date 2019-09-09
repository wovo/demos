
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "tests.hpp"

tests::tests(const i2c_ipass & i2c_ipass_object, const ADXL345 & ADXL345_object):
        i2c_ipass_object(i2c_ipass_object),
        ADXL345_object(ADXL345_object)
    {}
    


bool tests::test_i2c_ipass_read(){
    int read_data = i2c_ipass_object.read(0x00, 0x53);
    if(read_data == 229){
        return true;
    }
    return false;
}


bool tests::test_i2c_ipass_write(){
    i2c_ipass_object.write(0x20, 0x53, 8);
    int read_data = i2c_ipass_object.read(0x20, 0x53);
    if(read_data == 8){
        i2c_ipass_object.write(0x20, 0x53, 0);
        return true;
    }
    i2c_ipass_object.write(0x20, 0x53, 0);
    return false;
}


bool tests::test_ADXL345_measuring() {
    int axis_data[3];
    ADXL345_object.read_all_axis_2g(axis_data);
    hwlib::cout << hwlib::endl << "X: " << axis_data[0] << " Y: " << axis_data[1] << " Z: " << axis_data[2] << hwlib::endl;
    if((axis_data[0] == 0) && (axis_data[1] == 0) && (axis_data[2] == 0)){
        ADXL345_object.setup(1);
        hwlib::wait_ms(500);
        ADXL345_object.read_all_axis_2g(axis_data);
        hwlib::cout << "X: " << axis_data[0] << " Y: " << axis_data[1] << " Z: " << axis_data[2] << hwlib::endl;
        if((axis_data[0] != 0) && (axis_data[1] != 0) && (axis_data[2] != 0)){
            hwlib::cout << "Result: "; 
            return true;
        }
    }
    return false;
}


bool tests::test_ADXL345_set_standby_mode(){
    i2c_ipass_object.write(POWER_CTL, 0x53, 12);
    ADXL345_object.set_standby_mode();
    int read_data = i2c_ipass_object.read(POWER_CTL, 0x53);
    if(read_data == 4){
        i2c_ipass_object.write(POWER_CTL, 0x53, 0);
        return true;
    }
    i2c_ipass_object.write(POWER_CTL, 0x53, 0);
    return false;
}


void tests::print_test_results(){
    hwlib::cout << "Running tests" << hwlib::endl;
    hwlib::cout << "Test i2c_ipass read: " << test_i2c_ipass_read() << hwlib::endl;
    hwlib::cout << "Test i2c_ipass write: " << test_i2c_ipass_write() << hwlib::endl;
    hwlib::cout << "Test ADXL345 measuring: " << test_ADXL345_measuring() << hwlib::endl;
    hwlib::cout << "Test ADXL345 set standby mode: " << test_ADXL345_set_standby_mode() << hwlib::endl;
    hwlib::cout << "Finished running tests" << hwlib::endl;
}
