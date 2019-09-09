
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef CUBE_HPP
#define CUBE_HPP

class cube : public drawable {
protected:

   int radius;
 
public:

   cube( hwlib::window & w, const hwlib::xy & midpoint, int radius ):
      drawable( w, 
         midpoint - hwlib::xy( radius, radius ), 
         hwlib::xy( radius, radius ) * 2 ),
      radius( radius )
   {}
   
   void draw() override {
    for(int i = location.x; i < location.x + size.x; i++){
        for(int j = location.y; j < location.y + size.y; j++){
            w.write(hwlib::xy(i,j));
        }
    }
}
};

#endif
