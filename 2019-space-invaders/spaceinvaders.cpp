// ========================================================================
//
// File             : spaceinvaders.cpp
// Part of          : Spaceinvaders application using MPU6050 library
// MPU6050 Library  : https://github.com/theblindmick/MPU6050
// Copyright        : mickbos@hotmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// ========================================================================


#include "spaceinvaders.hpp"

void spaceinvaders::writeSpI(){
    w.write(hwlib::xy(12,10),S);
    w.write(hwlib::xy(20,10),P);
    w.write(hwlib::xy(28,10),A);
    w.write(hwlib::xy(36,10),C);
    w.write(hwlib::xy(43,10),E);
    w.write(hwlib::xy(51,10),I);
    w.write(hwlib::xy(59,10),N);
    w.write(hwlib::xy(67,10),V);
    w.write(hwlib::xy(75,10),A);
    w.write(hwlib::xy(83,10),D);
    w.write(hwlib::xy(91,10),E);
    w.write(hwlib::xy(99,10),R);
    w.write(hwlib::xy(107,10),S);
}

void spaceinvaders::writePtP(){
    w.write(hwlib::xy(32,44),P);
    w.write(hwlib::xy(40,44),R);
    w.write(hwlib::xy(48,44),E);
    w.write(hwlib::xy(56,44),S);
    w.write(hwlib::xy(64,44),S);
    w.write(hwlib::xy(72,44),space);
    w.write(hwlib::xy(80,44),T);
    w.write(hwlib::xy(88,44),O);
    w.write(hwlib::xy(48,52),P);
    w.write(hwlib::xy(56,52),L);
    w.write(hwlib::xy(64,52),A);
    w.write(hwlib::xy(72,52),Y);
}

void spaceinvaders::startscreen(){
    writeSpI();
    writePtP();
    w.flush();
}

// void spaceinvaders::start(){
//     // w.clear();
//     // FIRE.pullup_enable();   // Enables weak pull up
//     // FIRE.refresh();     //Refreshes the button buffer
//     // hwlib::wait_ms(100);
//     // startscreen();
//     // if(!FIRE.read()){
//     //     game();
//     // }
//     // else{
//     //     start();
//     // }
//     // hwlib::wait_ms(100);
//     game();
// };


void spaceinvaders::start(){
    bool ending = 0;
    startscreen();

    uint8_t currentRocket = 1;  // Next rocket to be fired 

    spaceship spaceship1(w, hwlib::xy(68,57), sensor1);
    spacealien spacealien1(w,hwlib::xy(10,0));
    spacealien spacealien2(w,hwlib::xy(40,0));
    spacealien spacealien3(w, hwlib::xy(70,0));
    spacealien spacealien4(w, hwlib::xy(100,0));
    rocket rocket1(w,hwlib::xy(-2,0));
    rocket rocket2(w,hwlib::xy(-2,0));
    rocket rocket3(w,hwlib::xy(-2,0));
    rocket rocket4(w,hwlib::xy(-2,0));
    rocket rocket5(w,hwlib::xy(-2,0));

    std::array< drawable *, 10 > objects = {&spacealien1, &spacealien2, &spacealien3, &spacealien4, &spaceship1, &rocket1, &rocket2, &rocket3, &rocket4, &rocket5};
    std::array< drawable *, 4 > aliens = {&spacealien1, &spacealien2, &spacealien3, &spacealien4};

    FIRE.refresh();

    while(FIRE.read()){
        w.clear();
        startscreen();
        hwlib::wait_ms(100);
    }

    while(!ending){
        w.clear();
        if(!FIRE.read()){
            switch(currentRocket){
                case 1: if(rocket1.destroyed){rocket1.fire(hwlib::xy(spaceship1.getLocation() + hwlib::xy(4,-3))); currentRocket +=1;  break;}

                case 2: if(rocket2.destroyed){rocket2.fire(hwlib::xy(spaceship1.getLocation() + hwlib::xy(4,-3))); currentRocket +=1;  break;}
        
                case 3: if(rocket3.destroyed){rocket3.fire(hwlib::xy(spaceship1.getLocation() + hwlib::xy(4,-3))); currentRocket +=1;  break;}
                
                case 4: if(rocket4.destroyed){rocket4.fire(hwlib::xy(spaceship1.getLocation() + hwlib::xy(4,-3))); currentRocket +=1;  break;}
                
                case 5: if(rocket5.destroyed){rocket5.fire(hwlib::xy(spaceship1.getLocation() + hwlib::xy(4,-3))); currentRocket = 1;  break;}
            }
        }
        for( auto & p : objects ){
            p->draw();
        }
        w.flush();
        FIRE.refresh();
        for( auto & p : objects ){
            p->update();
        }
        for( auto & p : objects ){
            for( auto & other : objects ){
                p->interact( *other );
            } 
        }
        for(auto & p : aliens){
            if(p->fucked == 1){
                ending = 1;
            }
        }
    }
    end();
};

void spaceinvaders::end(){
    w.clear();
    writePtP();
    while(FIRE.read()){
        start();
    }

}