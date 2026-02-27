/*
 *  drawfunc.cpp
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  03Nov06 TDK numToChar can do Hunger too.
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

char* numToChar( int num, bool isScore )
{
    char tempScore[20];
    char* scoreChar = new char[20];
	int startChar = 0;
	
	if( isScore )
	{
    	scoreChar[0] = 'S'; scoreChar[1] = 'c'; scoreChar[2] = 'o';
    	scoreChar[3] = 'r'; scoreChar[4] = 'e'; scoreChar[5] = ':';
    	scoreChar[6] = ' '; startChar = 7;
	}
	else
	{
		scoreChar[0] = 'H'; scoreChar[1] = 'u'; scoreChar[2] = 'n';
    	scoreChar[3] = 'g'; scoreChar[4] = 'e'; scoreChar[5] = 'r';
    	scoreChar[6] = ':'; scoreChar[7] = ' '; startChar = 8;
	}
    
    int i = 0;
    
    if( !num ) {
        scoreChar[startChar++] = '0';
        scoreChar[startChar++] = '\0';
    }
    while( num )
    {
        tempScore[i] = ((char) (num % 10)) + 48;
        num /= 10;
        i++;
    }
    
    int j = 0;
    for( ; j < i; j++ )
    {
        scoreChar[ j + startChar ] = tempScore[ i - 1 - j];
        if( ( i - j ) > 1 && (i - j - 1) % 3 == 0 )
        {
            i++; j++;
            scoreChar[j+startChar] = ',';
        }
    }
    if( j )
        scoreChar[ startChar + j ] = '\0';
    return scoreChar;
}
