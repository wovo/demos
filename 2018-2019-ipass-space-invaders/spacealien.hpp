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


#ifndef SPACEALIEN_HPP
#define SPACEALIEN_HPP

#include "spaceinvaders.hpp"
#include "drawable.hpp"

class spacealien : public drawable {
private:
    uint8_t timesdestroyed = 0;
    uint8_t speed = 1;
    bool isAlien = 1;
    const hwlib::xy aliencoords[26] = {
                        hwlib::xy(4,0),hwlib::xy(3,1),hwlib::xy(4,1),
                        hwlib::xy(5,1),hwlib::xy(2,2),hwlib::xy(3,2),
                        hwlib::xy(4,2),hwlib::xy(5,2),hwlib::xy(6,2),
                        hwlib::xy(1,3),hwlib::xy(3,3),hwlib::xy(4,3),
                        hwlib::xy(5,3),hwlib::xy(7,3),hwlib::xy(1,4),
                        hwlib::xy(2,4),hwlib::xy(3,4),hwlib::xy(4,4),
                        hwlib::xy(5,4),hwlib::xy(6,4),hwlib::xy(7,4),
                        hwlib::xy(3,5),hwlib::xy(5,5),hwlib::xy(2,6),
                        hwlib::xy(4,6),hwlib::xy(6,6)
                        };

public:
    spacealien(hwlib::window & w, const hwlib::xy location):
        drawable(w, location, hwlib::xy(9,7))
    {}

    bool fucked;

    /// \brief
    /// Draws the spacealien
    /// \details
    /// Draws the spacealien according to the coordinates written down
    /// in the aliencoords
    void draw() override;

    /// \brief
    /// Updates the location of spacealien::location
    /// \details
    /// Updates the location of the spacealien depending if destroyed or not
    void update() override;

    /// \brief
    /// checks if spacealien collides with another drawable
    /// \details
    /// Checks if the spacealien collides with another object.
    /// Upon collision, destroys itself and the other object and moves back to the top
    void interact(drawable & other);

}; // spacealien

#endif //SPACEALIEN_HPP