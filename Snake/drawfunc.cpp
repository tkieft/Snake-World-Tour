/*
 *  drawfunc.cpp
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  19Jun06 TDK Drawnum shall get its own class.
 *  18Jun06 TDK Add drawnum.
 *  12Jun06 TDK New Code.
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

char* scoreToChar( int score )
{
    char tempScore[20];
    char* scoreChar = new char[20];
    scoreChar[0] = 'S'; scoreChar[1] = 'c'; scoreChar[2] = 'o';
    scoreChar[3] = 'r'; scoreChar[4] = 'e'; scoreChar[5] = ':';
    scoreChar[6] = ' ';
    
    int i = 0;
    
    if( !score ) {
        scoreChar[7] = '0';
        scoreChar[8] = '\0';
    }
    while( score )
    {
        tempScore[i] = ((char) (score % 10)) + 48;
        score /= 10;
        i++;
    }
    
    int j = 0;
    for( ; j < i; j++ )
    {
        scoreChar[ j + 7 ] = tempScore[ i - 1 - j];
        if( ( i - j ) > 1 && (i - j - 1) % 3 == 0 )
        {
            i++; j++;
            scoreChar[j+7] = ',';
        }
    }
    if( j )
        scoreChar[ 7 + j ] = '\0';
    return scoreChar;
}