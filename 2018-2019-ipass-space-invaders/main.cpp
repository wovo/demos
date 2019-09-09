#include "hwlib.hpp"
#include "spaceinvaders.hpp"


int main(){	
   auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
   auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

   spaceinvaders game1(i2c_bus);
   game1.start();
}