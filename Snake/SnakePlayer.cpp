/*
 *  SnakePlayer.cpp
 *  Snake
 *
 *  Created by Tyler on 6/13/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 */

#include "SnakePlayer.h"

SnakePlayer::SnakePlayer( Uint32 snakeColor, string snakeName )
{
    color = snakeColor;
    name = snakeName;
    lives = 3;
    score = 0;
    direction = SNAKE_RIGHT;
    speed = 1;
}

int SnakePlayer::getLives() { return lives; }
int SnakePlayer::getScore() { return score; }
int SnakePlayer::getDirection() { return direction; }
int SnakePlayer::getSpeed() { return speed; }
Uint32 SnakePlayer::getColor() { return color; }
string SnakePlayer::getName() { return name; }
