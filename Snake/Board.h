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
#include "SnakePlayer.h"

class Board
{
private:
    SDL_Surface* scr;
    
public:
    /* Class-wide constants */
    const static int TILESIZE = 12;
    const static int LEVELSIZE = 35;
    const static int XLOC = 30;
    const static int YLOC = 30;
    
    const static Uint32 WALLCOLOR = 0xCC0000;
    const static Uint32 FLOORCOLOR = 0x0000CC;
        
    Board( SDL_Surface* sc );
    void draw( SnakePlayer* snakes[], int numSnakes );
};

#endif