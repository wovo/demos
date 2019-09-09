// ========================================================================
//
// File             : spaceinvaders.hpp
// Part of          : Spaceinvaders application using MPU6050 library
// MPU6050 Library  : https://github.com/theblindmick/MPU6050
// Copyright        : mickbos@hotmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// ========================================================================

#ifndef SPACEINVADERS_HPP
#define SPACEINVADERS_HPP

#include "spaceship.hpp"
#include "hwlib.hpp"
#include "mpu6050.hpp"
#include "drawable.hpp"
#include "rocket.hpp"
#include "spacealien.hpp"

class spaceinvaders {
private:
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;
    hwlib::glcd_oled w = hwlib::glcd_oled(i2c_bus, 0x3c);
    hwlib::target::pin_in FIRE = hwlib::target::pin_in(hwlib::target::pins::d40);//Digital Pin D40
    sensor sensor1 = sensor(i2c_bus);


    //Used letters
    hwlib::image_8x8 S = hwlib::image_8x8( 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00 );
    hwlib::image_8x8 P = hwlib::image_8x8( 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00 );
    hwlib::image_8x8 A = hwlib::image_8x8( 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00 );
    hwlib::image_8x8 C = hwlib::image_8x8( 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00 );
    hwlib::image_8x8 E = hwlib::image_8x8( 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00 );
    hwlib::image_8x8 I = hwlib::image_8x8( 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00 );
    hwlib::image_8x8 N = hwlib::image_8x8( 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00 );
    hwlib::image_8x8 V = hwlib::image_8x8( 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00 );
    hwlib::image_8x8 D = hwlib::image_8x8( 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00 );
    hwlib::image_8x8 R = hwlib::image_8x8( 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00 );
    hwlib::image_8x8 T = hwlib::image_8x8( 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00 );
    hwlib::image_8x8 O = hwlib::image_8x8( 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00 );
    hwlib::image_8x8 L = hwlib::image_8x8( 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00 );
    hwlib::image_8x8 Y = hwlib::image_8x8( 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00 );
    hwlib::image_8x8 space = hwlib::image_8x8( 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 );
public:


    spaceinvaders(hwlib::i2c_bus_bit_banged_scl_sda i2c_bus):
        i2c_bus(i2c_bus)
    {};

    /// \brief 
    /// Setups the game. 
    /// \details 
    /// Setups the game by printing Spaceinvaders and Press to play
    /// and waiting for button input
    void start();

    /// \brief
    /// Calls writeSpI() and writePtP();
    /// \details
    /// Setups the button, 
    void startscreen();

    /// \brief
    /// writes SpaceInvaders
    /// \details
    /// Writes the letters SpaceInvaders on screen
    void writeSpI();

    /// \brief
    /// Writes Press to Play
    /// \details
    /// Writes the lestters Press to Play on screen
    void writePtP();

    /// \brief
    /// End screen for when you are done
    /// \details
    /// Shows the score and possibility to try again
    void end();

    // /// \brief
    // /// Starts playing the game
    // /// \details
    // /// Handles the playing of the game
    // void game();
};

#endif //SPACEINVADERS_HPP