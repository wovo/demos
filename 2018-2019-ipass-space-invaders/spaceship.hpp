// ===================================================================
//
// File             : spacealien.hpp
// Part of          : Spaceinvaders application using MPU6050 library
// MPU6050 Library  : https://github.com/theblindmick/MPU6050
// Copyright        : mickbos@hotmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ===================================================================


#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "mpu6050.hpp"
#include "drawable.hpp"

class spaceship : public drawable {
private:
    sensor sensor1;
    int8_t lastuseddata;
    const hwlib::xy shipcoords[24] = {
                    hwlib::xy(4,0),hwlib::xy(4,1),hwlib::xy(3,2),
                    hwlib::xy(5,2),hwlib::xy(2,3),hwlib::xy(4,3),
                    hwlib::xy(6,3),hwlib::xy(0,4),hwlib::xy(2,4),
                    hwlib::xy(4,4),hwlib::xy(6,4),hwlib::xy(8,4),
                    hwlib::xy(0,5),hwlib::xy(1,5),hwlib::xy(2,5),
                    hwlib::xy(4,5),hwlib::xy(6,5),hwlib::xy(7,5),
                    hwlib::xy(8,5),hwlib::xy(0,6),hwlib::xy(3,6),
                    hwlib::xy(4,6),hwlib::xy(5,6),hwlib::xy(8,6)
                    };

public:
    spaceship(hwlib::window &w, const hwlib::xy & location, sensor &sensor1):
        drawable(w, location, hwlib::xy(9,7)),
        sensor1(sensor1)
    {};

    /// \brief
    /// Draws the spaceship
    /// \details
    /// Draws the spaceship according to the coordinates of the shipcoords array
    void draw() override;

    /// \brief
    /// Updates the spaceship::location 
    /// \details
    /// Reads the accelerometer data and updates the spaceship::location
    /// according to the fact if destroyed
    void update() override;

    /// \brief
    /// Returns spaceship::location
    /// \details
    /// Returns spaceship::location to be used with firing the rockets
    hwlib::xy getLocation();

}; //spaceship

#endif //SPACESHIP_HPP