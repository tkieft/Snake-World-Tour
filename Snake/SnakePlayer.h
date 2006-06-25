/*
 *  SnakePlayer.h
 *  Snake
 *
 *  Created by Tyler on 6/13/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  17Jun06 TDK Add moveQueue for hopefully more robust movement code
 *  16Jun06 TDK Eat! and Die!
 *  16Jun06 TDK Initial direction is now a parameter, add grow.
 *  15Jun06 TDK Add handleEvent().
 *  15Jun06 TDK Add length and getLength().
 *  13Jun06 TDK New Code.
 */

#ifndef SNAKEPLAYER_H
#define SNAKEPLAYER_H

#include "SDL.h"
#include <string>
#include <queue>
using std::queue;
using std::string;

class SnakePlayer
{
private:
    int lives;
    int score;
    int direction;
    int speed;
    int growFactor;
    SDL_Color color;
    string name;
    queue<int> moveQueue;
    
public:
    /* Class-wide constants */
    enum{ SNAKE_UP = 0, SNAKE_RIGHT = 1, SNAKE_DOWN = 2, SNAKE_LEFT = 3 };
    
    SnakePlayer( SDL_Color snakeColor, string snakeName, int startingDirection );
    
    int getLives();
    int getScore();
    int getDirection();
    int getSpeed();
    SDL_Color getColor();
    string getName();
    bool isGrowing();
    void eat();
    bool die();
    void reset( int dir );
    
    void updateDirection();
    void handleInput( SDL_Event* snakeEvent );
};

#endif
