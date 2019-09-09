#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "hwlib.hpp"

class block : public drawable{
protected:
    static constexpr bool texture[4][8][8] = {
    //brick texture
    {{1,1,1,1,0,1,1,1}, {1,1,1,1,0,1,1,1}, {0,0,0,0,0,0,0,0}, {1,1,0,1,1,0,1,1}, 
    {1,1,0,1,1,0,1,1}, {0,0,0,0,0,0,0,0}, {1,1,1,1,0,1,1,1}, {1,1,1,1,0,1,1,1}}, 
    
    //ground texture
    {{1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1}, 
    {1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1}},
    
    //question_block texture
    {{1,1,1,1,1,1,1,1}, {1,1,1,0,0,0,1,1}, {1,1,0,1,1,1,0,1}, {1,1,1,1,1,0,1,1}, 
    {1,1,1,1,0,1,1,1}, {1,1,1,1,1,1,1,1}, {1,1,1,1,0,1,1,1}, {1,1,1,1,1,1,1,1}},
    
    //coin texture
    {{0,0,0,0,0,0,0,0}, {0,0,1,1,1,0,0,0}, {0,1,1,1,1,1,0,0}, {0,1,1,1,1,1,0,0}, 
    {0,1,1,1,1,1,0,0}, {0,1,1,1,1,1,0,0}, {0,0,1,1,1,0,0,0}, {0,0,0,0,0,0,0,0}}
    };
    uint8_t pointer;
public:
    block(hwlib::xy location, hwlib::glcd_oled & display, uint8_t pointer ):
        drawable( location, display, pointer),
        pointer( pointer)
        {}
    //draw the object on the screen
    void draw()override{
        for(size_t i = 0; i < 8; i ++){
            for(size_t j = 0; j < 8; j ++){
                if(texture[pointer][i][j]){
                    display.write(hwlib::xy(j + location.x, i + location.y));
                }   
            }
        }
    }
};

#endif //BLOCK_HPP