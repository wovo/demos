#ifndef DUMMY_HPP
#define DUMMY_HPP

#include "hwlib.hpp"

class dummy : public drawable{
public:
    dummy(hwlib::glcd_oled & display):
        drawable(hwlib::xy(-255,-255), display, 7)
    {
        death = true;
    }
};

#endif //DUMMY_HPP