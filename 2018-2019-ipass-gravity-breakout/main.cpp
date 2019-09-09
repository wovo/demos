#include "hwlib.hpp"
#include "level.hpp"
#include "mpu6050.hpp"



int main( void ){	  
   namespace target = hwlib::target;

   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
   auto display = hwlib::glcd_oled( i2c_bus, 0x3c );  
   
   auto font    = hwlib::font_default_8x8();
   auto displayText = hwlib::terminal_from( display, font );

   mpu6050 chip(i2c_bus);
   
   int coin_counter = 0;
   
   auto jump = hwlib::target::pin_in( hwlib::target::pins::d14);

   auto mario1 = mario(hwlib::xy(16, 48), display, chip, jump);
   auto flagpole1 = flagpole(hwlib::xy(408, 8), display);
   
    //all drawables as variables
    auto a = question_block(hwlib::xy(48, 32), display);
    auto b = brick(hwlib::xy(40, 32), display);
    auto c = brick(hwlib::xy(56, 32), display);
    auto d = ground(hwlib::xy(8, 56), display);
    auto e = goomba(hwlib::xy(40, 48), display);
    auto f = ground(hwlib::xy(16, 56), display);
    auto g = ground(hwlib::xy(24, 56), display);
    auto h = ground(hwlib::xy(32, 56), display);
    auto i = ground(hwlib::xy(40, 56), display);
    auto j = ground(hwlib::xy(48, 56), display);
    auto k = ground(hwlib::xy(56, 56), display);
    auto l = ground(hwlib::xy(64, 56), display);
    auto m = ground(hwlib::xy(72, 56), display);
    auto n = ground(hwlib::xy(80, 56), display);
    auto o = ground(hwlib::xy(88, 56), display);
    auto p = ground(hwlib::xy(96, 56), display);
    auto q = ground(hwlib::xy(104, 56), display);
    auto r = ground(hwlib::xy(112, 56), display);
    auto s = ground(hwlib::xy(80, 48), display);
    auto t = goomba(hwlib::xy(88, 48), display);
    auto u = coin(hwlib::xy(16, 40), display, coin_counter); 
    auto v = coin(hwlib::xy(24, 40), display, coin_counter);
    auto w = coin(hwlib::xy(32, 40), display, coin_counter);
    auto x = coin(hwlib::xy(40, 40), display, coin_counter);
    auto y = coin(hwlib::xy(64, 40), display, coin_counter); 
    auto z = coin(hwlib::xy(72, 40), display, coin_counter);
    auto a2 = coin(hwlib::xy(88, 40), display, coin_counter);
    auto b2 = coin(hwlib::xy(96, 40), display, coin_counter);
    auto c2 = ground(hwlib::xy(120, 56), display);
    auto d2 = ground(hwlib::xy(128, 56), display);
    auto e2 = ground(hwlib::xy(136, 56), display);
    auto f2 = ground(hwlib::xy(136, 48), display);
    auto g2 = ground(hwlib::xy(168, 56), display);
    auto h2 = ground(hwlib::xy(176, 56), display);
    auto i2 = ground(hwlib::xy(184, 56), display);
    auto j2 = ground(hwlib::xy(192, 56), display);
    auto k2 = ground(hwlib::xy(200, 56), display);
    auto l2 = ground(hwlib::xy(208, 56), display);
    auto m2 = ground(hwlib::xy(216, 56), display);
    auto n2 = ground(hwlib::xy(224, 56), display);
    auto o2 = ground(hwlib::xy(232, 56), display);
    auto p2 = ground(hwlib::xy(240, 56), display);
    auto q2 = ground(hwlib::xy(280, 56), display);
    auto r2 = ground(hwlib::xy(296, 56), display);
    auto s2 = ground(hwlib::xy(264, 56), display);
    auto t2 = ground(hwlib::xy(272, 56), display);
    auto u2 = brick(hwlib::xy(200, 32), display);
    auto v2 = question_block(hwlib::xy(208, 32), display);
    auto w2 = brick(hwlib::xy(216, 32), display);
    auto x2 = ground(hwlib::xy(168, 48), display);
    auto y2 = coin(hwlib::xy(200, 24), display, coin_counter);
    auto z2 = coin(hwlib::xy(208, 24), display, coin_counter);
    auto a3 = coin(hwlib::xy(216, 24), display, coin_counter);
    auto b3 = goomba(hwlib::xy(176, 48), display);
    auto c3 = ground(hwlib::xy(136, 56), display);
    auto d3 = ground(hwlib::xy(136, 48), display);
    auto e3 = ground(hwlib::xy(168, 56), display);
    auto f3 = ground(hwlib::xy(176, 56), display);
    auto g3 = ground(hwlib::xy(232, 48), display);
    auto h3 = goomba(hwlib::xy(224, 48), display);
    auto i3 = ground(hwlib::xy(184, 56), display);
    auto j3 = ground(hwlib::xy(192, 56), display);
    auto k3 = ground(hwlib::xy(200, 56), display);
    auto l3 = ground(hwlib::xy(208, 56), display);
    auto m3 = ground(hwlib::xy(216, 56), display);
    auto n3 = ground(hwlib::xy(224, 56), display);
    auto o3 = ground(hwlib::xy(232, 56), display);
    auto p3 = ground(hwlib::xy(272, 56), display);
    auto q3 = ground(hwlib::xy(240, 48), display);
    auto r3 = ground(hwlib::xy(288, 56), display);
    auto s3 = ground(hwlib::xy(304, 56), display);
    auto t3 = ground(hwlib::xy(240, 40), display);
    auto u3 = ground(hwlib::xy(264, 48), display);
    auto v3 = ground(hwlib::xy(264, 40), display);
    auto w3 = ground(hwlib::xy(272, 48), display);
    auto x3 = ground(hwlib::xy(312, 56), display);
    auto y3 = ground(hwlib::xy(320, 56), display);
    auto z3 = ground(hwlib::xy(328, 56), display);
    auto a4 = ground(hwlib::xy(336, 56), display);
    auto b4 = ground(hwlib::xy(344, 56), display);
    auto c4 = ground(hwlib::xy(352, 56), display);
    auto d4 = ground(hwlib::xy(360, 56), display);
    auto e4 = ground(hwlib::xy(368, 56), display);
    auto f4 = ground(hwlib::xy(376, 56), display);
    auto g4 = ground(hwlib::xy(384, 56), display);
    auto h4 = ground(hwlib::xy(392, 56), display);
    auto i4 = ground(hwlib::xy(400, 56), display);
    auto j4 = ground(hwlib::xy(408, 56), display);
    auto k4 = ground(hwlib::xy(416, 56), display);
    auto l4 = ground(hwlib::xy(424, 56), display);
    auto m4 = ground(hwlib::xy(432, 56), display);
    auto n4 = coin(hwlib::xy(312, 40), display, coin_counter); 
    auto o4 = coin(hwlib::xy(312, 32), display, coin_counter);
    auto p4 = coin(hwlib::xy(320, 40), display, coin_counter);
    auto q4 = coin(hwlib::xy(320, 32), display, coin_counter);
    auto r4 = coin(hwlib::xy(328, 40), display, coin_counter); 
    auto s4 = coin(hwlib::xy(328, 32), display, coin_counter);
    auto t4 = coin(hwlib::xy(336, 40), display, coin_counter);
    auto u4 = coin(hwlib::xy(336, 32), display, coin_counter);
    auto v4 = coin(hwlib::xy(344, 40), display, coin_counter); 
    auto w4 = coin(hwlib::xy(344, 32), display, coin_counter);
    auto x4 = coin(hwlib::xy(352, 40), display, coin_counter);
    auto y4 = coin(hwlib::xy(352, 32), display, coin_counter);
    auto z4 = coin(hwlib::xy(360, 40), display, coin_counter); 
    auto a5 = coin(hwlib::xy(360, 32), display, coin_counter);
    auto b5 = coin(hwlib::xy(368, 40), display, coin_counter);
    auto c5 = coin(hwlib::xy(368, 32), display, coin_counter);
    auto d5 = dummy(display);
    auto e5 = dummy(display);
    auto f5 = dummy(display);

    //array with all objects
   std::array< drawable *,110> arrayObjects = {&a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, 
   &l, &m, &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z, &a2, &b2, &c2, &d2, &e2, &f2, 
   &g2, &h2, &i2, &j2, &k2, &l2, &m2, &n2, &o2, &p2, &q2, &r2, &s2, &t2, &u2, &v2, &w2, &x2, 
   &y2, &z2, &a3, &b3, &c3, &d3, &e3, &f3, &g3, &h3, &i3, &j3, &k3, &l3, &m3, &n3, &o3, &p3, 
   &q3, &r3, &s3, &t3, &u3, &v3, &w3, &x3, &y3, &z3, &a4, &b4, &c4, &d4, &e4, &f4, &g4, &h4, 
   &i4, &j4, &k4, &l4, &m4, &n4, &o4, &p4, &q4, &r4, &s4, &t4, &u4, &v4, &w4, &x4, &y4, &z4, 
   &a5, &b5, &c5, &d5, &e5, &f5};
   
   level level1(display, displayText, arrayObjects, mario1, flagpole1, 450, coin_counter);
   level1.play();
   
}
