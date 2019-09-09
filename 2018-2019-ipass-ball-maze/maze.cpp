// ===========================================================================
//
// Copyright Noah Titarsole (noah.titarsole@student.hu.nl) 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)
//
// ===========================================================================

#include "maze.hpp"

void start_game(hwlib::terminal_from & d){
   // hwlib::cout << "start game\n";
   d << "\f" << "\t0402" << "Ballmaze" << "\t0104" << "Noah Titarsole" << "\t0606" << "V1A"<< hwlib::flush;
      hwlib::wait_ms(2000);
      for(unsigned int i = 3; i > 0 ; i--){
         d << "\f" << "\t0402" << "Ballmaze"<< "\t0204" << "Starts in: " << i << hwlib::flush;
         hwlib::wait_ms(1000);
      }
   d << "\f" << hwlib::flush;
   hwlib::wait_ms(500);
}

void game_over(hwlib::terminal_from & d){
   // hwlib::cout << "game over\n";
   d << "\f" << "\t0303" << "Game over"  << hwlib::flush;
   hwlib::wait_ms(2000);
   d << "\f" << hwlib::flush;
   hwlib::wait_ms(500);
}

// ===========================================================================

bool game::within(int x, int a, int b){
   return ((x >= a) && (x <= b));
}

bool game::overlaps(const game & other){
   
   bool x_overlap = within(location.x, other.location.x, other.location.x + other.size.x) 
      || within(other.location.x, location.x, location.x + size.x);
     
   bool y_overlap = within(location.y, other.location.y, other.location.y + other.size.y) 
      || within(other.location.y, location.y, location.y + size.y);
   
   return x_overlap && y_overlap;
}

// ===========================================================================

void wall::draw(){
   hwlib::line x(location, end);
   x.draw(w);
}

// ===========================================================================

void player::draw(){
      hwlib::circle c(location + hwlib::xy(radius, radius), radius);
      c.draw(w);
   }

void player::update(){
   old_location.x = location.x;
   old_location.y = location.y;
   location = location + speed;
   // hwlib::cout << "old location: (" << old_location.x << ", " << old_location.y << ")\n";
   // hwlib::cout << "location(" << location.x << ", " << location.y << ")\n ";
}

void player::interact(game & other){
   if(this != & other){
      if(overlaps(other)){
         // hwlib::cout << "overlap\n";
         location = old_location;
         speed.x = 0;
         speed.y = 0;
      }
      else{
         // hwlib::cout << "no overlap\n";
         speed.x = get_accel_y();
         speed.y = get_accel_z();
      }
      // hwlib::cout << "speed: (" << speed.x << ", " << speed.y << ")\n";
   }
}

bool player::check(hwlib::terminal_from & d){
   if(location.x >= 121 && location.y == 51){   // Win coordinates
      winner(d);
      location.x = start.x;
      location.y = start.y;
   }
   else if(location.x <= 5 && location.y == 51){   // lose coordinates
      loser(d);
      location.x = start.x;
      location.y = start.y;
   }
   // hwlib::cout << "checked\n";
   if(t_lose == 3){
      return 1;
   }
   else{
      return 0;
   }
}

void player::winner(hwlib::terminal_from & d){
   // hwlib::cout << "win\n";
   s_wins++;
   t_wins++;
   d << "\f" << "\t0402" << "You win!" << "\t0004" << "Win streak = " << s_wins << "\t0006" << "Total wins = " << t_wins << hwlib::flush;   
   hwlib::wait_ms(2000);
   restart(d);
}

void player::loser(hwlib::terminal_from & d){
   // hwlib::cout << "lose\n";
   s_wins = 0;
   t_lose++;
   d << "\f" << "\t0402" << "You lose!" << "\t0004" << "lose streak = " << t_lose << "\t0006" << "Total wins = " << t_wins << hwlib::flush;   
   hwlib::wait_ms(2000);
   if(t_lose < 3){
      restart(d);
   }
}

void player::restart(hwlib::terminal_from & d){
   // hwlib::cout << "restart\n";
   for(unsigned int i = 3; i > 0 ; i--){
      d << "\f" << "\t0103" << "Restarts in: " << i << hwlib::flush;
      hwlib::wait_ms(1000);
   }
   d << "\f" << hwlib::flush;  
   hwlib::wait_ms(500);
}
