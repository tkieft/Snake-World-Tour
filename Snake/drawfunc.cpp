/*
 *  drawfunc.cpp
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 */

#include "drawfunc.h"
#include "globals.h"
#include "SDL.h"

void drawrect( int x, int y, int width, int height, Uint32 col, SDL_Surface* gScreen )
{
    for( int i = 0; i < height; i++ )
    {
        //vertical clipping
        if( ( y + i ) >= 0 && ( y + i ) < SCREENHEIGHT )
        {
            int len = width;
            int xofs = x;
            
            //left border
            if( xofs < 0 )
            {
                len += xofs;
                xofs = 0;
            }
            
            //right border
            if( xofs + len >= SCREENWIDTH )
                len -= ( xofs + len ) - SCREENWIDTH;
            
            int ofs = ( i + y ) * (gScreen->pitch / 4) + xofs;
            
            // note that len may be 0 at this point and no pixels get drawn
            
        for( int j = 0; j < len; j++ )
            ((unsigned int*)gScreen->pixels)[ofs + j] = col;
        }
    }
}