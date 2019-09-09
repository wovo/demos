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
#include <array>

int main(){
   namespace target = hwlib::target;

   auto scl       = target::pin_oc(target::pins::scl);
   auto sda       = target::pin_oc(target::pins::sda);
   auto i2c_bus   = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   auto w         = hwlib::glcd_oled(i2c_bus, 0x3c);

   auto font    = hwlib::font_default_8x8();
   auto d = hwlib::terminal_from(w, font);

   player p(w, hwlib::xy(115, 5), 4, i2c_bus, 0x68);
   wall top(w, hwlib::xy(0, 0), hwlib::xy(120, 0));
   wall left(w, hwlib::xy(0, 0), hwlib::xy(0, 60));
   wall right(w, hwlib::xy(120, 0), hwlib::xy(120, 50));
   wall bottom(w, hwlib::xy(0, 60), hwlib::xy(120, 60));
   wall x_1(w, hwlib::xy(11, 10), hwlib::xy(120, 10));
   wall x_2(w, hwlib::xy(0, 20), hwlib::xy(109, 20));
   wall x_3(w, hwlib::xy(11, 30), hwlib::xy(120, 30));
   wall x_4(w, hwlib::xy(0, 40), hwlib::xy(109, 40));
   wall x_5(w, hwlib::xy(0, 50), hwlib::xy(50, 50));
   wall x_6(w, hwlib::xy(70, 50), hwlib::xy(121, 50));

   p.initialize(3, 0);

   std::array< game *, 11 > objects = { &p, &top, &left, &right, &bottom, &x_1, &x_2, &x_3, &x_4, &x_5, &x_6 };

   start_game(d);

   for(;;){
      w.clear();

      for(auto & i : objects){
         i->draw();
      }
      w.flush();

      hwlib::wait_ms(75);

      for(auto & i : objects){
         i->update();
      }

      for(auto & i : objects){
         for(auto & other : objects){
            i->interact(*other);
         }
      }
      if(p.check(d)){
         game_over(d);
         break;
      }
   }
}
