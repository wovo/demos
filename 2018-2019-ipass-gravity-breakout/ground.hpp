#ifndef GROUND_HPP
#define GROUND_HPP

#include "hwlib.hpp"  

class ground : public block{
public:
    ground(hwlib::xy location, hwlib::glcd_oled & display):
        block( location, display, 1)
        {}

};

#endif //GROUND_HPP