#include "hwlib.hpp"
#include "registers.hpp"
//#include "helper.hpp"
#include "i2c_ipass.hpp"
#include "ADXL345.hpp"
#include "tests.hpp"
#include "drawable.hpp"
#include "line.hpp"
#include "cube.hpp"
#include "moving_cube.hpp"
#include "player.hpp"
 
int main( void ){
    
    namespace target = hwlib::target;
 
    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
 
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    
    auto btn1 = hwlib::target::pin_in( hwlib::target::pins::d22 );
    auto btn2 = hwlib::target::pin_in( hwlib::target::pins::d24 );
    auto btn3 = hwlib::target::pin_in( hwlib::target::pins::d26 );
    
    
    auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c );
    auto font    = hwlib::font_default_8x8();
    auto display = hwlib::terminal_from( oled, font );

    i2c_ipass i2c_ipass_object(i2c_bus);

    ADXL345 accelerometer(i2c_bus, 0x53, -5, 4, 8);
    ADXL345 accelerometer2(i2c_bus, 0x1D, 0, 2, -6);
    
    tests test_object(i2c_ipass_object, accelerometer);
    
    test_object.print_test_results();
    
    accelerometer.setup(1);
    accelerometer2.setup(1);    

    line top( oled, hwlib::xy(   0,  0 ), hwlib::xy( 127,  0 ) , hwlib::xy(1,-1));
    line right( oled, hwlib::xy( 127,  0 ), hwlib::xy( 127, 63 ), hwlib::xy(4,4) );
    line bottom( oled, hwlib::xy(   0, 63 ), hwlib::xy( 127, 63 ), hwlib::xy(1,-1) );
    line left( oled, hwlib::xy(   0,  0 ), hwlib::xy(   0, 63 ), hwlib::xy(3, 3)  );
    player player_1( oled, hwlib::xy(   10, 24 ), hwlib::xy(   10, 37  ), hwlib::xy(-1,1)  );
    player player_2( oled, hwlib::xy(   117, 24 ), hwlib::xy(   117, 37  ), hwlib::xy(-1,1)  );
    moving_cube mc( oled, hwlib::xy( 20, 27 ), 3, hwlib::xy( 5, 2 ) );

    std::array< drawable *, 7 > objects = { &mc, &top, &left, &right, &bottom, &player_1, &player_2 };
    
    int playing = 0;
 
    for(;;){
        if(btn1.read()){
            accelerometer.set_measuring_mode();
            hwlib::wait_ms(500);
        } else if (btn2.read()){
            accelerometer.set_standby_mode();
            hwlib::wait_ms(500);
        }
        
        
        if(playing == 0){
            if(btn3.read()){
                playing = 1;
                hwlib::wait_ms(500);
            }
            int axis_data[3];
        
            int axis_data2[3];
            
            accelerometer.read_all_axis_2g(axis_data);
            accelerometer2.read_all_axis_2g(axis_data2);

            display 
             << "\f" << "X: " << axis_data[0]
             << "\n" << "Y: " << axis_data[1]
             << "\n" << "Z: " << axis_data[2]
             << "\n"
             << "\n" << "X2: " << axis_data2[0]
             << "\n" << "Y2: " << axis_data2[1]
             << "\n" << "Z2: " << axis_data2[2]
             << hwlib::flush;
             
        } else {
            int player_1_y_axis = accelerometer.read_axis_2g(DATAY0,DATAY1);
            int player_2_y_axis = accelerometer2.read_axis_2g(DATAY0,DATAY1);
            
            if(player_1_y_axis > 30){
                player_1.set_speed(2);
            } else if(player_1_y_axis < -30){
                player_1.set_speed(-2);
            } else {
                player_1.set_speed(0);
            }
            
            if(player_2_y_axis > 30){
                player_2.set_speed(2);
            } else if(player_2_y_axis < -30){
                player_2.set_speed(-2);
            } else {
                player_2.set_speed(0);
            }
            
            oled.clear();
            for( auto & p : objects ){
             p->draw();
            }
            oled.flush();
            hwlib::wait_ms( 100 );
            for( auto & p : objects ){
              p->update();
            }
            for( auto & p : objects ){
             for( auto & other : objects ){
                p->interact( *other );
             } 
            }
        }
    }
}
