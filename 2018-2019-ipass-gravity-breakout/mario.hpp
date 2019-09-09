#ifndef MARIO_HPP
#define MARIO_HPP

#include "hwlib.hpp" 
#include "mpu6050.hpp" 

class mario : public entity{
private:
    mpu6050 & chip;
    hwlib::target::pin_in & jump;
    uint8_t jumping;
    bool able_to_jump;
public:
    mario(hwlib::xy location, hwlib::glcd_oled & display, mpu6050 & chip, hwlib::target::pin_in & jump):
        entity( location, display, 0),
        chip( chip),
        jump( jump),
        jumping( 0 ),
        able_to_jump( 0 )
        {}
        

    //get mario's next x-move
    int get_next_move_x(){
        chip.disableSleep();
        return chip.get_position_y() / 10;
    }
    
    //get mario's next y-move and give him gravity
    int get_next_move_y(){
        if(jumping == 1){
            jumping++;
            return -6;
        }else if(jumping == 2){
            jumping++;
            return -6;
        }else if(jumping == 3){
            jumping = 0;
            able_to_jump = false;
            return -6;
        }else if(!jump.read()){
            if(able_to_jump){
                jumping = 1;
                return -6;
            }
        }
        return 2;
    }
    
    void initialiseNextMove()override{
        next_position = hwlib::xy(location.x + get_next_move_x(), location.y + get_next_move_y());
    }
    
    void executeNextMove()override{
        //update the direction mario is facing
        if(next_position.x > location.x){
            direction = 1;
        }else if(next_position.x < location.x){
            direction = 0;
        }
        
        //check if he fell from the map
        if(next_position.y > 64){
            death = true;
        }
        
        //if he bumped into a block, stop the jump
        if(next_position.y > location.y - 6){
            jumping = 0;
            able_to_jump = false;
        }
        
        //if he is standing, enable jump again
        if(next_position.y == location.y){
            able_to_jump = true;
        }
        
        drawable::executeNextMove();
    }
    
    void interact(drawable & other)override{
        //if other is goomba
        if(other.get_type() == 5){
            if(will_overlap(other)){
                if(location.y >= other.get_location().y){
                    death = true;
                }
            }
        }
        entity::interact(other);
    }
    
    bool ending_scene(drawable & other){
        //mario's climbing down from the flagpole animation
        location.y += 3;
        if(location.y >= other.get_location().y + 42){
            return true;
        }
        return false;
    }

};

#endif //MARIO_HPP