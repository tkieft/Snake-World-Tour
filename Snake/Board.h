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
    
public:
    /* Class-wide constants */
    const static int TILESIZE = 12;
    const static int LEVELSIZE = 35;
    const static int XLOC = 30;
    const static int YLOC = 30;
        
    Board( SDL_Surface* sc );
    void draw();
};

#endif