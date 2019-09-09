
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef PLAYER_HPP
#define PLAYER_HPP

class player : public line {
private:
    int speed = 0;
   
public:

    player( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & end, const hwlib::xy & moving_cube_angle):
      line( w, location, end, moving_cube_angle)
    {}
    
    void set_speed(const int & new_speed){
        speed = new_speed;
    }
   
    void update() override {
        location.y = location.y + speed;
        end.y = end.y + speed;      
    }
   
};

#endif
