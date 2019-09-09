// ===================================================================
//
// File             : rocket.hpp
// Part of          : Spaceinvaders application using MPU6050 library
// MPU6050 Library  : https://github.com/theblindmick/MPU6050
// Copyright        : mickbos@hotmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ===================================================================


#ifndef ROCKET_HPP
#define ROCKET_HPP

#include "drawable.hpp"

class rocket : public drawable {
private:
    int8_t speed = 5;
public:
    rocket(hwlib::window &w, const hwlib::xy location):
        drawable(w,location, hwlib::xy(1,1))
    {};

    /// \brief
    /// Draws the rocket based on rocket::location
    /// \details
    /// Draws the rocket based on rocket::location
    void draw() override;

    /// \brief
    /// Updates rocket::location
    /// \details
    /// Updates rocket::location based on the fact if the rocket is destroyed,
    /// and if the rocket is leaving the screen
    void update() override;

    /// \brief
    /// "Fires" the rocket
    /// \details
    /// "Fires" the rocket by anti destroying it and moving it to the location of the spaceship
    void fire(hwlib::xy moveTo);

}; // rocket

#endif //ROCKET_HPP