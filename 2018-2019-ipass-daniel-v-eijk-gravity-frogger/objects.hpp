// Copyright Daniel Bulkowski van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

/// @file

#include "hwlib.hpp"
#include "mpu6050.hpp"

/// \brief
/// A class for all in-game cars
/// \details
/// A class made for the oncoming in-game traffic and a super-class for the player-controlled
/// vehicle
class car{
protected:
    hwlib::window & display;
    hwlib::xy start;
    hwlib::xy location;
    hwlib::xy size;
    hwlib::xy end;
public:
    /// \brief
    /// Constructor for the car class
    /// \details
    /// The constructor takes a hwlib::window & display, hwlib::xy start and hwlib::xy location
    /// as variables.
    /// Start stands for the starting positions of the vehicles and location for their current
    /// location.
    /// The size of the vehicle is always 10 by 10 and the end is calculated by adding the location
    /// to the size.
    car(hwlib::window & display, hwlib::xy start, hwlib::xy location):
        display(display),
        start(start),
        location(location),
        size(hwlib::xy(10, 10)),
        end(hwlib::xy(location.x + size.x, location.y + size.y))
    {}

    /// \brief
    /// Compare 3 integers
    /// \details
    /// Checks whether the first integer lies between the second and third ones
    bool within(int x, int a, int b);

    /// \brief
    /// Compares locations
    /// \details
    /// Compares the location of the car with the location and size of the other car
    /// Using within() it checks whether the 2 cars overlap and thus hit each other
    bool overlaps(car & other);

    /// \brief
    /// Returns location
    /// \details
    /// Returns the saved location variable
    hwlib::xy getLocation();

    /// \brief
    /// Sets location
    /// \details
    /// Sets the current location of a car to the desired position and adjusts the end
    /// of the car accordingly
    void setLocation(const hwlib::xy & newLocation);

    /// \brief
    /// Returns start
    /// \details
    /// Returns the starting location of the car
    hwlib::xy getStart();

    /// \brief
    /// Updates the car variables
    /// \details
    /// In the oncoming traffic's case this function simply moves the cars forward and
    /// checks whether they've passed a certain point, if they have passed this point
    /// the cars get a random chance to appear again thus creating a unique wave of 
    /// oncoming traffic every time the user passes a wave
    virtual void update(mpu6050 & sensor);
    
    /// \brief
    /// Draws the car
    /// \details
    /// In the oncoming traffic's case this funtion draws a square at the current location
    /// representing the oncoming cars
    virtual void draw();
    
    /// \brief
    /// Does nothign
    /// \details
    /// In the oncoming traffic's case this function does absolutely nothing and only exists
    /// so the user's car can use it without complicating the code of the application
    virtual void interact(car & other){};
};

/// \brief
/// A class for the player vehicle
/// \details
/// A subclass of car that creates and controls the user's vehicle
class player : public car{
private:
    int lives;
    int score;
public:
    /// \brief
    /// Constructor for player
    /// \details
    /// The constructor takes hwlib::window & and hwlib::xy variables, in this variables
    /// case the location of the vehicle in the first frame is the same as the start and
    /// is thus set to be the same
    /// The amount of lives is set to 3 but can be changed by using a certain function
    /// The score always starts at 0
    player(hwlib::window & display, hwlib::xy start):
        car(display, start, start),
        lives(3),
        score(0)
    {}

    /// \brief
    /// Updates the variables within player
    /// \details
    /// Moves the player left or right according to what is measured with the acceleration-
    /// sensor's x axis
    void update(mpu6050 & sensor) override;

    /// \brief
    /// Draws the player vehicle
    /// \details
    /// In the player's case this function draws a traingle with its point faced upwards
    /// that represents the player vehicle
    void draw() override;

    /// \brief
    /// Manages interaction between vehicles
    /// \details
    /// Checks whether the player vehicle overlaps with the oncoming vehicles using the
    /// overlap and within functions it inherited from car
    /// Should the player have enough lives to survive the collision then their lives will
    /// go down by one, the oncoming car's position will be reset and the player can continue
    /// playing.
    /// If the player doesn't have enough lives left, they get a GAME OVER screen, their score
    /// is shown and the game exits
    /// If the player vehicle doesn't collide with anything then the score goes up
    void interact(car & other) override ;

    /// \brief
    /// Returns lives
    /// \details
    /// Returns the amount of lives the player has left
    int getLives();

    /// \brief
    /// Sets lives
    /// \details
    /// Used to set the amount of lives the player has
    void setLives(const int & newLives);
};

/// \brief
/// A class for the lines on the road
/// \details
/// A class made specifically for the lines shown on the road that move along with
/// the cars
class lines{
private:
    hwlib::window & display;
    hwlib::xy start;
    hwlib::xy location;
    hwlib::xy size;
    hwlib::xy end;
public:
    /// \brief
    /// Constructor for lines
    /// \details
    /// A constructor for lines that takes a hwlib::window & and 2 hwlib::xy's as variables
    /// Start stands for the starting positions of the vehicles and location for their current
    /// location.
    /// The size of the vehicle is always 10 by 10 and the end is calculated by adding the location
    /// to the size.
    lines(hwlib::window & display, hwlib::xy start, hwlib::xy size):
        display(display),
        start(start),
        location(start),
        size(size),
        end(hwlib::xy(location.x + size.x, location.y + size.y))
    {}

    /// \brief
    /// Draws the lines
    /// \details
    /// Draws multiple lines that move along with the oncoming traffic, giving the illusion
    /// that the player is moving
    void draw();

    /// \brief
    /// Updates
    /// \details
    /// Updates the variables in the class
    /// The location changes so the lines move along with the oncoming traffic, giving the
    /// illusion that the player is moving forward
    /// The lines continue moving untill the location hits a certain point at which they're
    /// reset
    void update();
};