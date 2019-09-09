#ifndef COIN_HPP
#define COIN_HPP

#include "hwlib.hpp"

class coin : public block{
private:
    int & coin_counter;
public:
    coin(hwlib::xy location, hwlib::glcd_oled & display, int & coin_counter):
        block( location, display, 3), 
        coin_counter( coin_counter)
        {}
        
    void interact(drawable & other)override{
        //if mario will be at the same place as a coin
        if(other.get_type() == 4){
            if(will_overlap(other)){
                coin_counter ++;
                death = true;
        
            }
        }
    }

};


#endif //COIN_HPP