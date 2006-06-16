/*
 *  SnakePlayer.cpp
 *  Snake
 *
 *  Created by Tyler on 6/13/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  16Jun06 TDK Initial Direction is now a parameter, add grow.
 *  15Jun06 TDK Add length and getLength().
 *  13Jun06 TDK New Code.
 */

#include "SnakePlayer.h"

SnakePlayer::SnakePlayer( Uint32 snakeColor, string snakeName, int startingDirection )
{
    color = snakeColor;
    name = snakeName;
    lives = 3;
    score = 0;
    direction = SNAKE_UP;
    speed = 1;
    growFactor = 5;
}

int SnakePlayer::getLives() { return lives; }
int SnakePlayer::getScore() { return score; }
int SnakePlayer::getDirection() { return direction; }
int SnakePlayer::getSpeed() { return speed; }
Uint32 SnakePlayer::getColor() { return color; }
string SnakePlayer::getName() { return name; }

bool SnakePlayer::isGrowing()
{
    if( growFactor > 0 )
    {
        growFactor--;
        return true;
    }
    return false;
}

void SnakePlayer::handleInput( SDL_Event* snakeEvent )
{
    switch( snakeEvent->key.keysym.sym )
    {
        case SDLK_LEFT:
            if( direction != SNAKE_RIGHT )
                direction = SNAKE_LEFT;
            break;
        case SDLK_RIGHT:
            if( direction != SNAKE_LEFT )
                direction = SNAKE_RIGHT;
            break;
        case SDLK_UP:
            if( direction != SNAKE_DOWN )
                direction = SNAKE_UP;
            break;
        case SDLK_DOWN:
            if( direction != SNAKE_UP )
                direction = SNAKE_DOWN;
            break;
        default:
            break;
    }
}