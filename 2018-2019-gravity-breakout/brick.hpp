#ifndef BRICK_HPP
#define BRICK_HPP 

#include "hwlib.hpp"  

class brick : public block{
public:
    brick(hwlib::xy location, hwlib::glcd_oled & display):
        block( location, display, 0)
        {}

};

#endif //BRICK_HPP