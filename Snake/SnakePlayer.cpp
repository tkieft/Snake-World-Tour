/*
 *  SnakePlayer.cpp
 *  Snake
 *
 *  Created by Tyler on 6/13/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  15Jun06 TDK Add length and getLength().
 *  13Jun06 TDK New Code.
 */

#include "SnakePlayer.h"

SnakePlayer::SnakePlayer( Uint32 snakeColor, string snakeName )
{
    color = snakeColor;
    name = snakeName;
    lives = 3;
    length = 3;
    score = 0;
    direction = SNAKE_RIGHT;
    speed = 1;
}

int SnakePlayer::getLives() { return lives; }
int SnakePlayer::getScore() { return score; }
int SnakePlayer::getDirection() { return direction; }
int SnakePlayer::getSpeed() { return speed; }
int SnakePlayer::getLength() { return length; }
Uint32 SnakePlayer::getColor() { return color; }
string SnakePlayer::getName() { return name; }

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