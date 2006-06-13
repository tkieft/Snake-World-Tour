/*
 *  Board.h
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include "SDL.h"

class Board
{
private:
    SDL_Surface* scr;
    SDL_Rect offset;
    
public:
    Board( SDL_Surface* sc );
    void draw();
};

#endif