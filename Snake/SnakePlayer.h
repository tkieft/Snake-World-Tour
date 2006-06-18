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
    Uint32 color;
    string name;
    queue<int> moveQueue;
    
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
    Uint32 getColor();
    string getName();
    bool isGrowing();
    void eat();
    void die();
    void reset();
    void updateDirection();
};

#endif