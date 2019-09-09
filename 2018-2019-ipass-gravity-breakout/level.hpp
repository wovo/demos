#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "hwlib.hpp"
#include "drawable.hpp"
#include "block.hpp"
#include "entity.hpp"
#include "ground.hpp"
#include "brick.hpp"
#include "question_block.hpp"
#include "mario.hpp"
#include "level.hpp"
#include "mpu6050.hpp"
#include "coin.hpp"
#include "goomba.hpp"
#include "flagpole.hpp"
#include "dummy.hpp"
#include <array>

class level{
private:
    hwlib::glcd_oled & display;
    hwlib::terminal_from & displayText;
    std::array<drawable *,110> arrayObjects;
    mario & mario1;
    flagpole flagpole1;
    int current_position;
    int length;
    int & coin_counter;
    int amountIterations;
    
    
public:
    level(hwlib::glcd_oled & display, hwlib::terminal_from & displayText, std::array< drawable *, 110> arrayObjects, mario & mario1, flagpole flagpole1, int length, 
    int & coin_counter, int amountIterations = -1):
        display( display),
        displayText( displayText ),
        arrayObjects( arrayObjects ),
        mario1( mario1 ),
        flagpole1( flagpole1),
        current_position( mario1.get_location().x),
        length( length),
        coin_counter( coin_counter),
        amountIterations( amountIterations)

        {}

    //this function will calculate the movement of all onjects compared to the camera
    int calculate_movement_objects(int next_move_mario){
        current_position += next_move_mario;
        if(current_position < 64 || length - current_position < 64){
            return 0;
        }else{
            return -next_move_mario;
        }
    }
    
    bool check_if_mario_wins(){
        //if mario is at the flagpole
        if(mario1.get_location().x >= flagpole1.get_location().x){
            //mario will climb down the flagpole
            for(;;){
                display.clear();
                if(mario1.ending_scene(flagpole1)){
                    break;
                }
                mario1.draw();
                flagpole1.draw();
                for(auto object : arrayObjects){
                    if(object->is_dead()){
                        continue;
                    }
                    if(object->get_location().x >= -8 && object->get_location().x <= 136){
                        object->draw();
                    }
                }
                display.flush();
            }
            display.clear();
            displayText << "\f" << "you win" << "\n" << "you had " << coin_counter << " coins!";
            display.flush();
            return true;
        }
        return false;
    } 
    
        
    ///\brief
    ///main loop
    void play(){
        //if no amountIterations is specified, it will be an infinite loop
        for(int i = 0; i < amountIterations || amountIterations == -1; i++){
            //initialise for all objects on screen their next move
            mario1.initialiseNextMove();
            for( auto & object : arrayObjects){
                if(object->is_dead()){
                    continue;
                }
                //if objects is near screen
                if(object->get_location().x >= -8 && object->get_location().x <= 136){
                    object->initialiseNextMove();
                }
            }
            //let all objects on screen interact with mario and update his next move if necessary
            for( const auto & other : arrayObjects){
                if(other->is_dead()){
                    continue;
                }
                mario1.interact(*other);
            }
            
            //let all non-dead objects on screen interact with each other and update their next move if necessary
            for( auto  & object : arrayObjects){
                if(object->get_location().x >= -8 && object->get_location().x <= 136){
                    if(object->is_dead()){
                        continue;
                    }
                    for( const auto & other : arrayObjects){
                        if(other->is_dead()){
                            continue;
                        }
                        if(object == other){
                            continue;
                        }
                        if(other->get_location().x >= -8 && other->get_location().x <= 136){
                            object->interact(*other);
                        }
                    }
                    object->interact(mario1);
                }
            }
            
            //calculate new objects position compared to camera
            int next_move_mario = mario1.get_next_position().x - mario1.get_location().x;
            int next_move_objects = calculate_movement_objects(next_move_mario);
            
            //update all non-dead objects current location with their next moves
            mario1.executeNextMove();
            for( auto object : arrayObjects){
                if(object->is_dead()){
                    continue;
                }
                if(object->get_location().x >= -8 && object->get_location().x <= 136){
                    object->executeNextMove();
                }
            }
            //check if mario is dead
            if(mario1.is_dead()){
                display.clear();
                displayText << "\f" << "game over";
                display.flush();
                break;
            }
            //check if mario has won
            if(check_if_mario_wins()){
                break;
            }
            
            //update all non-dead objects compared to the shifting of the camera and draw the objects near screen
            display.clear();
            displayText << "\f" << "ox"<< coin_counter;
            mario1.update_position(next_move_objects);
            mario1.draw();
            flagpole1.update_position(next_move_objects);
            flagpole1.draw();
            for(auto & object : arrayObjects){
                if(object->is_dead()){
                    continue;
                }
                object->update_position(next_move_objects);
                if(object->get_location().x >= -8 && object->get_location().x <= 136){
                    object->draw();
                }

            }
            //display.write(hwlib::xy(10,10));
            display.flush();
        
        }
    }
};
#endif //LEVEL_HPP