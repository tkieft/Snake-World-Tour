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
#include "SnakePlayer.h"


Board::Board ( SDL_Surface* sc ) : scr( sc ) {}

void Board::draw( SnakePlayer* snakes[], int numSnakes )
{
    Uint32 color;
    int tile;
    
    if( SDL_MUSTLOCK( scr ) )
        if( SDL_LockSurface( scr ) < 0 )
            return;
    
    for( int y = 0; y < LEVELSIZE; y++ )
        for( int x = 0; x < LEVELSIZE; x++ )
        {
            tile = levels[0][ y * LEVELSIZE + x ];
            if( tile == LEVEL_FLOOR )
                color = FLOORCOLOR;
            else if( tile == LEVEL_WALL )
                color = WALLCOLOR;
            else if( tile >= 10 && tile < 400 )
                color = snakes[0]->getColor();
            else if( numSnakes == 2 && tile >= 400 )
                color = snakes[1]->getColor();
                
            drawrect( XLOC + x * TILESIZE, YLOC + y * TILESIZE, TILESIZE, TILESIZE, color, scr);
        }
    if( SDL_MUSTLOCK( scr ) )
        SDL_UnlockSurface( scr );
    
    SDL_UpdateRect( scr, XLOC, YLOC, XLOC - 1 + TILESIZE * LEVELSIZE, YLOC - 1 + TILESIZE * LEVELSIZE );            
}