/*
 *  SnakePlayer.cpp
 *  Snake
 *
 *  Created by Tyler on 6/13/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  17Jun06 TDK Move static constant definitions here.
 *  17Jun06 TDK Make input handling more robust.
 *  16Jun06 TDK Eat! and Die!
 *  16Jun06 TDK Initial Direction is now a parameter, add grow.
 *  15Jun06 TDK Add length and getLength().
 *  13Jun06 TDK New Code.
 */

#include "SnakePlayer.h"

const int SnakePlayer::SNAKE_UP = 0;
const int SnakePlayer::SNAKE_RIGHT = 1;
const int SnakePlayer::SNAKE_DOWN = 2;
const int SnakePlayer::SNAKE_LEFT = 3;

SnakePlayer::SnakePlayer( Uint32 snakeColor, string snakeName, int startingDirection ) : moveQueue()
{
    color = snakeColor;
    name = snakeName;
    lives = 3;
    score = 0;
    direction = startingDirection;
    speed = 1;
    growFactor = 5;
}

int SnakePlayer::getLives() { return lives; }
int SnakePlayer::getScore() { return score; }
int SnakePlayer::getDirection() { return direction; }
int SnakePlayer::getSpeed() { return speed; }
Uint32 SnakePlayer::getColor() { return color; }
string SnakePlayer::getName() { return name; }
void SnakePlayer::die() { lives--; }
void SnakePlayer::reset() { direction = SNAKE_UP; speed = 1; growFactor = 5; }

bool SnakePlayer::isGrowing()
{
    if( growFactor > 0 )
    {
        growFactor--;
        return true;
    }
    return false;
}

void SnakePlayer::eat()
{
    growFactor += 3;
    score += 50;
}

void SnakePlayer::updateDirection()
{
    if( !moveQueue.empty() )
    {
        switch( moveQueue.front() )
        {
            case SNAKE_LEFT:
                if( direction != SNAKE_RIGHT )
                    direction = SNAKE_LEFT;
                break;
            case SNAKE_RIGHT:
                if( direction != SNAKE_LEFT )
                    direction = SNAKE_RIGHT;
                break;
            case SNAKE_UP:
                if( direction != SNAKE_DOWN )
                    direction = SNAKE_UP;
                break;
            case SNAKE_DOWN:
                if( direction != SNAKE_UP )
                    direction = SNAKE_DOWN;
                break;
            default:
                break;
        }
        moveQueue.pop();
    }
}

void SnakePlayer::handleInput( SDL_Event* snakeEvent )
{
    switch( snakeEvent->key.keysym.sym )
    {
        case SDLK_LEFT: case SDLK_a:
            moveQueue.push( SNAKE_LEFT );
            break;
        case SDLK_RIGHT: case SDLK_d:
            moveQueue.push( SNAKE_RIGHT );
            break;
        case SDLK_UP: case SDLK_w:
            moveQueue.push( SNAKE_UP );
            break;
        case SDLK_DOWN: case SDLK_s:
            moveQueue.push( SNAKE_DOWN );
            break;
        default:
            break;
    }
}
