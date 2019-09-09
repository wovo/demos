#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP 

#include "hwlib.hpp"

class drawable{
protected:
    hwlib::xy location;
    hwlib::xy next_position;
    hwlib::glcd_oled & display;
    uint8_t type_id;
    //type-ids:
    //brick = 0
    //ground = 1
    //question_block = 2
    //coin = 3
    //mario = 4
    //goomba = 5
    //flagpole = 6
    //dummy = 7
    bool death;

public:
    drawable( hwlib::xy location, hwlib::glcd_oled & display , uint8_t type_id):
        location( location ),
        next_position( location),
        display( display ),
        type_id( type_id),
        death( 0 )
        {}
    
    //draw the object on screen
    virtual void draw(){};
    
    //overlaps only works with 2 8x8 objects
    bool will_overlap(const drawable & other){
        if(other.get_next_position().x > next_position.x - 8 && other.get_next_position().x < next_position.x + 8){
            if(other.get_next_position().y > next_position.y - 8 && other.get_next_position().y < next_position.y + 8){
                return true;
            }
        }
    return false;
    }
    
    //this function will update all objects position compared to the 128x64 display they are rendered on
    void update_position(int next_move_others){
        location.x += next_move_others;
    }
    
    //let all objects near screen interact with all other objects near screen
    virtual void interact(drawable & other){};
    
    //let all objects near screen initialise their next position
    virtual void initialiseNextMove(){
        next_position = location;
    }
    
    //all objects on screen will change their location to their next position
    virtual void executeNextMove(){
        location = next_position;
    }
    
    //return location
    hwlib::xy get_location()const{
        return location;
    }
    
    //return next position
    hwlib::xy get_next_position()const{
        return next_position;
    }
    
    //return type-id
    uint8_t get_type()const{
        return type_id;
    }
    
    //return true if object is dead and should be ignored in the main loop
    bool is_dead()const{
        return death;
    }
    
    //this function can break block and make them dead
    void kill(){
        death = true;
    }
};

#endif //DRAWABLE_HPP