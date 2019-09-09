#include "hwlib.hpp"
#include "mpu6050.hpp"
    
int16_t mpu6050::read_from_adress(uint8_t adressByte){
    hwlib::i2c_write_transaction(i2c_bus, adress).write(adressByte);
    int8_t byte1 = hwlib::i2c_read_transaction(i2c_bus, adress).read_byte();
    int8_t byte2 = hwlib::i2c_read_transaction(i2c_bus, adress).read_byte();
    int16_t byte3 = ( byte1 << 8) + byte2;
    return byte3;
}

mpu6050::mpu6050(hwlib::i2c_bus_bit_banged_scl_sda & i2c_bus, uint8_t adress):
    i2c_bus( i2c_bus ),
    adress( adress ),
    scale_range_accel( 0 )
    {}
    
void mpu6050::accel_config(uint8_t value){
    if(value > 3){
        value = 3;
    }else if( value < 0){
        value = 0;
    }
    scale_range_accel = value;
    value <<= 3;
    const uint8_t array[2] = {0x1C, value};
    hwlib::i2c_write_transaction(i2c_bus, adress).write(array, 2); 
    hwlib::wait_ms(100);
}

void mpu6050::return_formatted_data(){        
    hwlib::cout << "x = " << get_position_x() << "*  y = " << get_position_y() << "*  z = " << get_position_z() 
    << "* temp = " << get_temperature_in_C() << " C  " << get_temperature_in_K() << " K  " << get_temperature_in_F() << " F " 
    " gyro x = " << get_gyro_x() << "  gyro y = " << get_gyro_y() << "  gyro z = " << get_gyro_z() << hwlib::endl;
    hwlib::wait_ms(500);
}
    
void mpu6050::disableSleep(){
    const uint8_t array[2] = {0x6b, 0x00};
    hwlib::i2c_write_transaction(i2c_bus, adress).write(array, 2); 
    hwlib::wait_ms(100);
}
    
void mpu6050::enableSleep(){
    const uint8_t array[2] = {0x6b, 0xC0};
    hwlib::i2c_write_transaction(i2c_bus, adress).write(array, 2); 
    hwlib::wait_ms(100);
}

void mpu6050::freeze(){
    const uint8_t array[2] = {0x6b, 0x40};
    hwlib::i2c_write_transaction(i2c_bus, adress).write(array, 2); 
    hwlib::wait_ms(100);
}
    
int8_t mpu6050::get_position_x(){
    float value = read_from_adress(0x3b);
    value /= (16384 >> scale_range_accel);
    value *= 90;
    if(value > 90){
        value = 90;
    }
    if(value < -90){
        value = -90;
    }
    return value;
}

int8_t mpu6050::get_position_y(){
    float value = read_from_adress(0x3d);
    value /= (16384 >> scale_range_accel);
    value *= 90;
    if(value > 90){
        value = 90;
    }
    if(value < -90){
        value = -90;
    }
    return value;        
}

int8_t mpu6050::get_position_z(){
    float value = read_from_adress(0x3f);
    value /= (16384 >> scale_range_accel);
    value *= 90;
    if(value > 90){
        value = 90;
    }
    if(value < -90){
        value = -90;
    }
    return value;
}
    
int16_t mpu6050::get_temperature_in_C(){
    float value = read_from_adress(0x41);
    value /= 340;
    value += 36.53;
    return value;
}

int16_t mpu6050::get_temperature_in_K(){
    float value = get_temperature_in_C();
    value += 273.15;
    return value;
}
    
int16_t mpu6050::get_temperature_in_F(){
    float value = get_temperature_in_C();
    value *= 1.8;
    value += 32;
    return value;
}

int mpu6050::get_gyro_x(){        
    float value = read_from_adress(0x43);
    return value;
}

int mpu6050::get_gyro_y(){
    float value = read_from_adress(0x45);
    return value;
}

int mpu6050::get_gyro_z(){
    float value = read_from_adress(0x47);
    return value;
}