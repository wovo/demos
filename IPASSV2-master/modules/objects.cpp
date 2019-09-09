// Copyright Daniel Bulkowski van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

/// @file

#include "objects.hpp"
#include <ctime>
#include <array>

bool car::within(int x, int a, int b){
   return ((x >= a) && (x <= b)) || ((x >= b) && (x <= a));
}

bool car::overlaps(car & other){
    bool backOverlap = within(
        location.y,
        other.location.y,
        other.location.y + other.size.y
    ) && (within(
        location.x,
        other.location.x,
        other.location.x + other.size.x
    ) || within(
        location.x + size.x,
        other.location.x,
        other.location.x + other.size.x
    ));

    bool frontOverlap = within(
        end.y,
        other.location.y,
        other.location.y + size.y
    ) && within(
        location.x + (size.x / 2),
        other.location.x,
        other.location.x + size.x
    );
   
   return backOverlap || frontOverlap;
}

hwlib::xy car::getLocation(){
    return location;
}

void car::setLocation(const hwlib::xy & newLocation){
    location = newLocation;
    end = hwlib::xy(newLocation.x + size.x, newLocation.y + size.y);
}

hwlib::xy car::getStart(){
    return start;
}

void car::update(mpu6050 & sensor) {
    if(location.y > 70){
        if((rand() % 12) == 1){
            location.y = start.y - 9;
            end = hwlib::xy(start.x + size.x, start.y - 9 + size.y);
        }
    } else {
        location.y += 2;
        end.y += 2;
    }
}

void car::draw(){
    hwlib::line top(location, hwlib::xy(end.x, location.y));
    hwlib::line left(location, hwlib::xy(location.x, end.y));
    hwlib::line right(hwlib::xy(end.x, location.y), end);
    hwlib::line bottom(hwlib::xy(location.x, end.y), hwlib::xy(end.x + 1, end.y));
    top.draw(display);
    left.draw(display);
    right.draw(display);
    bottom.draw(display);
}

void player::update(mpu6050 & sensor){
    int accel = sensor.getAccelY();
    // Left
    if(accel >= 2 && location.x > 1){
        location.x -= 2;
        end.x -= 2;
    }
    // Right
    if(accel <= -2 && location.x < 116){
        location.x += 2;
        end.x += 2;
    }
}

void player::draw(){
    hwlib::line bottom(location, hwlib::xy(location.x + size.x, location.y));
    hwlib::line left(location, hwlib::xy(location.x + (size.x / 2) + 1, end.y));
    hwlib::line right(hwlib::xy(end.x, end.y + 10), hwlib::xy(end.x - (size.x / 2) - 1, end.y));
    bottom.draw(display);
    left.draw(display);
    right.draw(display);
}

void player::interact(car & other){
    if(!(location.x == other.getLocation().x && location.y == other.getLocation().y)){
        if(overlaps(other) && lives > 0){
            display.clear();
            auto font = hwlib::font_default_8x8();
            auto oled = hwlib::terminal_from(display, font);
            lives--;
            oled << "LIVES: " << lives;
            display.flush();
            other.setLocation(hwlib::xy(other.getStart().x, other.getStart().y));
            score -= 100;
            hwlib::wait_ms(2000);
        } else if(overlaps(other) && lives == 0){
            display.clear();
            auto font = hwlib::font_default_8x8();
            auto oled = hwlib::terminal_from(display, font);
            oled << "GAME OVER\n SCORE: " << score / 100;
            display.flush();
            other.setLocation(hwlib::xy(other.getStart().x, other.getStart().y));
            lives = -2;
            hwlib::wait_ms(5000);
        } else {
            score++;
        }
    }
}

int player::getLives(){
    return lives;
}

void player::setLives(const int & newLives){
    lives = newLives;
    end.y -= 20;
}

void lines::draw(){
    hwlib::line negativefirst(hwlib::xy(location.x, location.y - 40), hwlib::xy(location.x, location.y - 30));
    hwlib::line zero(hwlib::xy(location.x, location.y - 20), hwlib::xy(location.x, location.y - 10));
    hwlib::line first(location, hwlib::xy(location.x, location.y + 10));
    hwlib::line second(hwlib::xy(location.x, location.y + 20), hwlib::xy(location.x, location.y + 30));
    hwlib::line third(hwlib::xy(location.x, location.y + 40), hwlib::xy(location.x, location.y + 50));
    negativefirst.draw(display);
    zero.draw(display);
    first.draw(display);
    second.draw(display);
    third.draw(display);
}

void lines::update(){
    if(location.y > 16){
        location.y = start.y;
        end = hwlib::xy(start.x + size.x, start.y + size.y);
    } else {
        location.y += 2;
        end.y += 2;
    }
}