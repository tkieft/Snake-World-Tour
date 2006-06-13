/*
 *  Board.cpp
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 */

#include "Board.h"
#include "levels.h"
#include "drawfunc.h"
#include "globals.h"


Board::Board ( SDL_Surface* sc ) : scr( sc ) {}

void Board::draw()
{
    Uint32 color;
    
    if( SDL_MUSTLOCK( scr ) )
        if( SDL_LockSurface( scr ) < 0 )
            return;
    
    for( int y = 0; y < LEVELSIZE; y++ )
        for( int x = 0; x < LEVELSIZE; x++ )
        {
            switch( levels[0][ y * LEVELSIZE + x ])
            {
                case LEVEL_FLOOR:
                    color = FLOORCOLOR;
                    break;
                case LEVEL_WALL:
                    color = WALLCOLOR;
                    break;
            }
            drawrect( XLOC + x * TILESIZE, YLOC + y * TILESIZE, TILESIZE, TILESIZE, color, scr);
        }
    if( SDL_MUSTLOCK( scr ) )
        SDL_UnlockSurface( scr );
    
    SDL_UpdateRect( scr, XLOC, YLOC, XLOC - 1 + TILESIZE * LEVELSIZE, YLOC - 1 + TILESIZE * LEVELSIZE );
            
}