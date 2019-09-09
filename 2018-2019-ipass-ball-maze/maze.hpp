// ===========================================================================
//
// Copyright Noah Titarsole (noah.titarsole@student.hu.nl) 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)
//
// ===========================================================================

#ifndef MAZE
#define MAZE

#include "mpu6050.hpp"

void start_game(hwlib::terminal_from & d);

void game_over(hwlib::terminal_from & d);

// ===========================================================================

class game{
protected:

   hwlib::window & w;
   hwlib::xy location;
   hwlib::xy size;
   hwlib::xy start;
   int s_wins = 0;
   int t_wins = 0;
   int t_lose = 0;
   
public:

   game(hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size):
      w(w),
      location(location),
      size(size),
      start(location)
   {}  
   
   virtual void draw() = 0;
   virtual void update(){};
   bool overlaps(const game & other);   
   virtual void interact(game & other){};
   bool within(int x, int a, int b);
   
};

// ===========================================================================

class wall : public game{
public:

   hwlib::xy end;

   wall(hwlib::window & w, const hwlib::xy & location, const hwlib::xy & end):
      game(w, location, end - location),
      end(end)
   {}
   
   void draw() override;
};

// ===========================================================================

class player : public game, public mpu6050{
private:

   int radius;
   hwlib::xy speed = {0, 0};
   hwlib::xy old_location;
   
public:

   player(hwlib::window & w, const hwlib::xy & midpoint, int radius, hwlib::i2c_bus & bus, uint_fast8_t address):
      game(w, midpoint - hwlib::xy(radius, radius), hwlib::xy(radius, radius) * 2),
      mpu6050(bus, address),
      radius(radius)
   {}
   
   void draw() override;

   void update() override;

   void interact(game & other) override;

   bool check(hwlib::terminal_from & d);

   void winner(hwlib::terminal_from & d);

   void loser(hwlib::terminal_from & d);

   void restart(hwlib::terminal_from & d);
};

#endif //MAZE