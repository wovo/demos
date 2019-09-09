// ===================================================================
//
// File             : spacealien.cpp
// Part of          : Spaceinvaders application using MPU6050 library
// MPU6050 Library  : https://github.com/theblindmick/MPU6050
// Copyright        : mickbos@hotmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ===================================================================


#include "spacealien.hpp"

void spacealien::draw(){
    if(!destroyed){
        for(uint8_t i = 0; i < 26; i++){
            w.write(location + aliencoords[i]);
        }
    }
};

void spacealien::update(){
    if(!destroyed){
        if((location.y + speed) <= 56){
            location.y = location.y+speed;
        }
        else{
            drawable::fucked = true;
        }
    }
    else{
        timesdestroyed +=1;
        if(timesdestroyed == 20){
            destroyed = false;
        }
    }
};

void spacealien::interact(drawable & other){
    if( this != & other){
        if( overlaps( other )){
            location.y = 0;
            destroyed = true;
            other.destroyed = true;
        }
    }           
};
