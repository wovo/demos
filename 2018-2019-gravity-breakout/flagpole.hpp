#ifndef FLAGPOLE_HPP
#define FLAGPOLE_HPP

#include "hwlib.hpp"

class flagpole : public drawable{
private:
    bool texture[48][5] = {
        {0,0,0,1,0}, {0,0,1,1,1}, {0,0,0,1,0}, {0,0,1,1,0}, {0,1,1,1,0}, {1,1,1,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, 
        {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, 
        {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, 
        {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, 
        {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, 
        {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,0,1,0}, {0,0,1,1,1}, {0,0,1,1,1}, {0,0,1,1,1}
        };
public:
    flagpole(hwlib::xy location, hwlib::glcd_oled & display):
        drawable(location, display, 6)
        {}
        
    void draw()override{
        for(unsigned int i = 0; i < 48; i ++){
            for(unsigned int j = 0; j < 5; j++){
                if(texture[i][j]){
                    display.write(hwlib::xy(j + location.x, i + location.y));
                }
            }
        }
    }
};



#endif //FLAGPOLE_HPP