
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef MOVING_CUBE_HPP
#define MOCING_CUBE_HPP

class moving_cube : public cube {
private:

   hwlib::xy speed;
   int score_1 = 0;
   int score_2 = 0;
   
public:

   moving_cube( 
      hwlib::window & w, 
      const hwlib::xy & midpoint, 
      int radius, 
      const hwlib::xy & speed 
   ):
      cube( w, midpoint, radius ),
      speed( speed )  
   {}
   
   void update() override {
      location = location + speed; 
   }
   
   void interact( drawable & other ) override {
      if( this != & other){
         if( overlaps( other )){
            auto moving_cube_angle = other.get_moving_cube_angle();
            if(moving_cube_angle.x < 2 && moving_cube_angle.y < 2){
                speed.x *= moving_cube_angle.x;
                speed.y *= moving_cube_angle.y;
            } else {
                if(moving_cube_angle.x == 3){
                    score_2 += 1;
                    location.x = 20;
                    location.y = 27;
                    speed.x = 5;
                    speed.y = 2;                    
                } else if(moving_cube_angle.x == 4) {
                    score_1 += 1;
                    location.x = 107;
                    location.y = 27;
                    speed.x = -5;
                    speed.y = -2;
                }
                w.clear();
                auto font    = hwlib::font_default_8x8();
                auto display = hwlib::terminal_from( w, font );
                if(score_1 < 4 && score_2 < 4){
                display 
                     << "\t0503" << score_1 << " - " << score_2
                     << hwlib::flush;
                } else {
                    if(score_1 == 4){
                         display 
                             << "\t0303" << " P1 WINS!!"
                             << hwlib::flush;
                    } else {
                        display 
                             << "\t0303" << " P2 WINS!!"
                             << hwlib::flush;
                    }
                    score_1 = 0;
                    score_2 = 0;
                }
                hwlib::wait_ms(1000);
            }
         }
      }
   }   
};

#endif
