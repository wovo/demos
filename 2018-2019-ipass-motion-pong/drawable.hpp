
//          Copyright Dylan Griffioen.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <hwlib.hpp>

class drawable {
protected:

    hwlib::window & w;
    hwlib::xy location;
    hwlib::xy size;
    hwlib::xy moving_cube_angle = {1,1};
   
public:

    drawable( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size ):
      w( w ),
      location( location ),
      size( size )
   {}  

   drawable( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size, const hwlib::xy moving_cube_angle ):
      w( w ),
      location( location ),
      size( size ),
      moving_cube_angle(moving_cube_angle)
   {}      
   
   virtual void draw() = 0;
   virtual void update(){}
   bool overlaps( const drawable & other );   
   virtual void interact( drawable & other ){}
   
   hwlib::ostream & print( hwlib::ostream & out ) const {
      return out << location << " " << ( location + size );
   }

    hwlib::xy get_moving_cube_angle() {
        return moving_cube_angle;
    }
};

hwlib::ostream & operator<<( hwlib::ostream & lhs, const drawable & rhs ){
   return rhs.print( lhs );
}

bool within( int x, int a, int b ){
   return ( x >= a ) && ( x <= b );
}

bool drawable::overlaps( const drawable & other ){
   
   bool x_overlap = within( 
      location.x, 
      other.location.x, 
      other.location.x + other.size.x
   ) || within( 
      other.location.x, 
      location.x, 
      location.x + size.x
   );
     
   bool y_overlap = within( 
      location.y, 
      other.location.y, 
      other.location.y + other.size.y
   ) || within( 
      other.location.y, 
      location.y, 
      location.y + size.y
   );
   
   return x_overlap && y_overlap;
}


#endif
