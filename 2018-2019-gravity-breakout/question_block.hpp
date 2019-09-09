#ifndef QUESTION_BLOCK_HPP
#define QUESTION_BLOCK_HPP

#include "hwlib.hpp"  

class question_block : public block{

public:
    question_block(hwlib::xy location, hwlib::glcd_oled & display):
        block( location , display, 2)
        {}

};

#endif //QUESTION_BLOCK_HPP