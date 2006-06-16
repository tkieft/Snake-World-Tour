/*
 *  SnakePlayer.h
 *  Snake
 *
 *  Created by Tyler on 6/13/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  16Jun06 TDK Initial direction is now a parameter, add grow.
 *  15Jun06 TDK Add handleEvent().
 *  15Jun06 TDK Add length and getLength().
 *  13Jun06 TDK New Code.
 */

#ifndef SNAKEPLAYER_H
#define SNAKEPLAYER_H

#include "SDL.h"
#include <string>
using std::string;

class SnakePlayer
{
private:
    int lives;
    int score;
    int direction;
    int speed;
    int length;
    int growFactor;
    Uint32 color;
    string name;
    
public:
    /* Class-wide constants */
    const static int SNAKE_UP = 0;
    const static int SNAKE_RIGHT = 1;
    const static int SNAKE_DOWN = 2;
    const static int SNAKE_LEFT = 3;
    
    SnakePlayer( Uint32 snakeColor, string snakeName, int startingDirection );
    
    void handleInput( SDL_Event* snakeEvent );
    
    int getLives();
    int getScore();
    int getDirection();
    int getSpeed();
    int getLength();
    Uint32 getColor();
    string getName();
    bool isGrowing();
};

#endif