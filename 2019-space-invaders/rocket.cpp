// ===================================================================
//
// File             : rocket.cpp
// Part of          : Spaceinvaders application using MPU6050 library
// MPU6050 Library  : https://github.com/theblindmick/MPU6050
// Copyright        : mickbos@hotmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ===================================================================


#include "rocket.hpp"

void rocket::draw(){
    for(uint8_t i = 0; i < 3; i++){
        w.write(hwlib::xy(location.x, location.y-i));
    }
};

void rocket::update(){
    if(!destroyed){
        if((location.y - speed) > 0){
            location.y = location.y - speed;
        }
        else{
            destroyed = true;
            location = hwlib::xy(-2,0);
        }
    }
    else{
        location = hwlib::xy(-2,0);
    }
};

void rocket::fire(hwlib::xy moveTo){
    if(location == hwlib::xy(-2,0)){
        destroyed = false;
        location = moveTo;
    }
};