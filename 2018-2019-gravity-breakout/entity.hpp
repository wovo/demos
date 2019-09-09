#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "hwlib.hpp"

class entity : public drawable{
protected:    
    bool direction;
    static constexpr bool texture[2][8][8] = {
        //mario's texture
        {{0,0,1,1,1,0,0,0}, {0,0,1,1,1,1,1,0}, {0,0,1,1,1,0,0,0}, {0,0,1,1,1,1,0,0}, 
        {0,1,1,1,1,1,0,0}, {1,0,1,1,1,1,1,0}, {0,0,1,1,1,1,0,0}, {0,0,1,0,0,1,0,0}},
        //goomba's texture
        {{0,0,0,1,1,0,0,0}, {0,0,1,1,1,1,0,0}, {0,1,0,1,1,0,1,0}, {0,1,1,1,1,1,1,0}, 
        {1,1,1,1,1,1,1,1}, {0,0,1,1,1,1,0,0}, {0,0,1,1,1,1,0,0}, {0,1,1,0,0,1,1,0}},
        
    };
        
    uint8_t pointer;
public:
    entity(hwlib::xy location, hwlib::glcd_oled & display, uint8_t pointer):
        drawable( location, display, pointer + 4),
        direction( 1 ),
        pointer( pointer)
        {}
    
    //draw the object facing right when direction is true and facing left when direction is false
    void draw()override{
        for(unsigned int i = 0; i < 8; i ++ ){
            for(unsigned int j = 0; j < 8; j ++){
                if(texture[pointer][i][j]){
                    if(direction){
                        display.write(hwlib::xy(j + location.x, i + location.y));
                    }else{
                        display.write(hwlib::xy( 7 - j + location.x, i + location.y));
                    }  
                }
            }
        }
    }
    
    //interact entities with blocks and don't let them overlap
    void interact(drawable & other)override{
        //other is brick, question_block or ground
        if(other.get_type() >= 0 && other.get_type() <= 2){
            //if you will overlap the other in the next position
            if(will_overlap(other)){
                //if you are currently under the object
                if(location.y > other.get_location().y
                && !(other.get_location().x - location.x >= location.y - other.get_location().y)
                && !(location.x - other.get_location().x >= location.y - other.get_location().y)){
                   next_position.y = other.get_next_position().y + 8;
                   //if block is not ground, break it
                   if(other.get_type() != 1){
                        other.kill();
                   }    
                }
                //if you are currently above the object
                else if(location.y < other.get_location().y
                && !(other.get_location().x - location.x >= other.get_location().y - location.y)
                && !(location.x - other.get_location().x >= other.get_location().y - location.y)){
                    next_position.y = other.get_next_position().y - 8;
                }
                //if you are currently at the right side of the object
                else if(location.x > other.get_location().x
                && !(other.get_location().y - location.y >= location.x - other.get_location().x)
                && !(location.y - other.get_location().y >= location.x - other.get_location().x)){
                   next_position.x = other.get_next_position().x + 8;
                }
                //if you are currently at the left side of the object
                else if(location.x < other.get_location().x
                && !(other.get_location().y - location.y >= other.get_location().x - location.x)
                && !(location.y - other.get_location().y >= other.get_location().x - location.x)){
                    next_position.x = other.get_next_position().x - 8;
                }
            }
        }
        
        
    }
    
};

#endif //ENTITY_HPP