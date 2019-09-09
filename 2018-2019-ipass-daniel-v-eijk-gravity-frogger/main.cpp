// Copyright Daniel Bulkowski van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include "objects.hpp"

int main(){
    // Create necessary variables to connect with oled display and sensor
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto i2c = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    auto display = hwlib::glcd_oled(i2c, 0x3c);
    auto font = hwlib::font_default_8x8();
    auto oled = hwlib::terminal_from(display, font);

    mpu6050 sensor = mpu6050(i2c);

    // Activate, set sensitivity and calibrate the sensor
    sensor.activate();
    sensor.setSensitivity(3, 3);
    sensor.calibrate();

    // Create necessary variables to display the game
    car first = car(display, hwlib::xy(0, 0), hwlib::xy(0, 80));
    car second = car(display, hwlib::xy(23, 0), hwlib::xy(23, 80));
    car third = car(display, hwlib::xy(46, 0), hwlib::xy(46, 80));
    car fourth = car(display, hwlib::xy(68, 0), hwlib::xy(68, 80));
    car fifth = car(display, hwlib::xy(90, 0), hwlib::xy(90, 80));
    car sixth = car(display, hwlib::xy(112, 0), hwlib::xy(112, 80));

    player user = player(display, hwlib::xy(55, 60));

    lines firstsecond = lines(display, hwlib::xy(16, 0), hwlib::xy(0, 70));
    lines secondthird = lines(display, hwlib::xy(39, 0), hwlib::xy(0, 70));
    lines thirdfourth = lines(display, hwlib::xy(62, 0), hwlib::xy(0, 70));
    lines fourthfifth = lines(display, hwlib::xy(84, 0), hwlib::xy(0, 70));
    lines fifthsixth = lines(display, hwlib::xy(106, 0), hwlib::xy(0, 70));

    std::array<car *, 7> cars = {&first, &second, &third, &fourth, &fifth, &sixth, &user};
    std::array<lines *, 5> road = {&firstsecond, &secondthird, &thirdfourth, &fourthfifth, &fifthsixth};

    // Display intro for the game
    display.clear();
    oled << "    Made by:" << "\n\n" << "Daniel Bulkowski" << "\n" << "  van Eijk-Bos" 
        << "\n" << "      V1A";
    display.flush();
    hwlib::wait_ms(5000);
    display.clear();

    // Set the amount of lives the user gets
    user.setLives(0);
    // Endlessly loop through the variables to update and draw them until the user is out of lives
    for(;;){
        display.clear();
        for(auto & car : cars){
            car->update(sensor);
            car->draw();
            for(auto & other : cars){
                car->interact(*other);
            }
        }
        for(auto & line : road){
            line->update();
            line->draw();
        }
        // End game is user is out of lives
        if(user.getLives() == -2){
            break;
        }
        display.flush();
    }
}