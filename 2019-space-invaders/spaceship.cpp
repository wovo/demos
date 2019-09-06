// ===================================================================
//
// File             : spaceship.cpp
// Part of          : Spaceinvaders application using MPU6050 library
// MPU6050 Library  : https://github.com/theblindmick/MPU6050
// Copyright        : mickbos@hotmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ===================================================================


#include "spaceship.hpp"

void spaceship::draw() {
    for(uint8_t i = 0; i < 24; i++){
        w.write(location+shipcoords[i]);
    }
};

void spaceship::update() {
    int8_t acceldata = sensor1.readAccel().y;

    if(!destroyed){
        if((location.x + acceldata) < 121 && (location.x + acceldata) > 0){
            location.x = location.x + acceldata;
        }
        else{
            if((location.x + acceldata) <=0 ){
                    location.x = 0;
                }
            else{
                location.x = 121;
            }
        }

    }
}

hwlib::xy spaceship::getLocation(){
    return location;
}