#ifndef GOOMBA_HPP
#define GOOMBA_HPP

#include "hwlib.hpp"

class goomba : public entity{
public:
    goomba(hwlib::xy location, hwlib::glcd_oled & display):
        entity( location, display, 1)
        {}
    
    void initialiseNextMove()override{
        int temp;
        if(direction){
            temp = 2;
        }else{
            temp = -2;        
        }
        next_position = hwlib::xy(location.x + temp, location.y + 2);
    }
    
    void executeNextMove()override{
        //if goomba walks into something and cannot continue walking, reverse
        if(location.x == next_position.x){
            direction ^= 1;
        }
        drawable::executeNextMove();
    }
    
    void interact(drawable & other)override{
        //if the other is mario and will jump on the goomba
        if(other.get_type() == 4){
            if(will_overlap(other)){
                if(other.get_location().y < location.y){
                    death = true;
                }
            }
        }
        entity::interact(other);
    }
};

#endif //GOOMBA_HPP