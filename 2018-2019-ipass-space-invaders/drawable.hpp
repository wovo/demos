#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "hwlib.hpp"

class drawable {
protected:

   hwlib::window & w; //Window or screen to display
   hwlib::xy location; // Right upper corner of object
   hwlib::xy size;

   

public:
   bool destroyed = false;
   bool fucked = 0;

   drawable( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size ):
      w( w ),
      location( location ),
      size( size )
   {}      
   
   /// \brief
   /// Virtual draw function
   virtual void draw() = 0;

   /// \brief
   /// Virtual update function
   virtual void update(){};

   /// \brief
   /// to check if overlaps
   /// \details
   /// Returns 1 if the hitbox of a drawable is
   /// within another drawable
   bool overlaps( const drawable & other );   

   /// \brief
   /// To check if object is within another object
   /// \ details
   /// Return 1 if a object is within another object
   virtual void interact( drawable & other ){};
      
   /// \brief
   /// Hwlib::cout print operator
   /// \details
   /// Prints the location + size of a drawable
   hwlib::ostream & print( hwlib::ostream & out ) const {
      return out << location << " " << ( location + size );
   }      
   };

hwlib::ostream & operator<<( hwlib::ostream & lhs, const drawable & rhs );

bool within( int x, int a, int b );
#endif //DRAWABLE_HPP