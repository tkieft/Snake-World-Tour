/*
 *  NumberDrawer.cpp
 *  Snake
 *
 *  Created by Tyler on 6/19/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  19Jun06 TDK New Code.
 */

#include "Timer.h"
#include <iostream>

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    stoppedTicks = 0;
    paused = false;
    started = false;
    stopped = false;
}

void Timer::Init( string pathToResources )
{
    nums = load_image( pathToResources + "nums.bmp" );
    calcNumSize();
}

void Timer::calcNumSize()
{
    if( SDL_MUSTLOCK( nums ) )
        if( SDL_LockSurface( nums ) < 0 )
            return;
    
    int x, y, k;
    // k loops through the characters ( 11 of them =  0-9 and : )
    for( k = 0; k < 11; k++ )
    {
        numsOfs[k] = nums->w;
        numsWidth[k] = 0;
        
        // x and y loop through font data
        for( y = 0; y < NUMHEIGHT; y++ )
        {
            for( x = 0; x < NUMWIDTH; x++ )
            {
                if( ((Uint32*)nums->pixels)[ y * SWIDTH + k * NUMWIDTH + x ] != 0xFFFFFF )
                {
                    if( NUMWIDTH * k + x < numsOfs[k] )
                        numsOfs[k] = NUMWIDTH * k + x;
                    if( NUMWIDTH * k + x > numsWidth[k] )
                        numsWidth[k] = NUMWIDTH * k + x;
                }
            }
        }
        numsWidth[k] -= numsOfs[k];
        std::cout << numsWidth[k] << " ";
    }
    
    if( SDL_MUSTLOCK( nums ) ) SDL_UnlockSurface( nums );
}

Timer::~Timer()
{
    SDL_FreeSurface( nums );
}

void Timer::start()
{
    started = true;
    paused = false;
    stopped = false;
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    stoppedTicks = SDL_GetTicks();
    started = false;
    paused = false;
    stopped = true;
}

int Timer::get_ticks()
{
    if( started )
    {
        if( paused )
            return pausedTicks;
        else
            return SDL_GetTicks() - startTicks;
    }
    else if( stopped )
        return stoppedTicks - startTicks;

    return 0;
}

void Timer::pause()
{
    if( started && !paused )
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if( paused )
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

void Timer::draw( int x, int y, SDL_Surface* gScreen )
{
    if( SDL_MUSTLOCK( nums ) )
        if( SDL_LockSurface( nums ) < 0 )
            return;
    
    int min = get_ticks() / 1000 / 60 ;
    int s1 = (( get_ticks() / 1000 ) % 60 ) / 10;
    int s2 = (( get_ticks() / 1000 ) % 60 ) % 10;
    
    drawOne( x, y, min, gScreen );
    drawOne( x, y, 10, gScreen ); // colon
    drawOne( x, y, s1, gScreen );
    drawOne( x, y, s2, gScreen );
    
    if( SDL_MUSTLOCK( nums ) ) SDL_UnlockSurface( nums );
}

void Timer::drawOne( int& x, int& y, int num, SDL_Surface* gScreen )
{
    //std::cout << x << " " << y << "\n";
    //keep track of screen x offset;
    int x0, scrloc, numloc;
    for( int i = 0; i < NUMHEIGHT; i++ )
    {
        x0 = 0;
        for( int j = numsOfs[num]; j < numsOfs[num] + numsWidth[num]; j++ )
        {
            scrloc = ( y + i ) * gScreen->pitch / 4 + x + x0;
            numloc = i * SWIDTH + j;
            if( ((Uint32*)nums->pixels)[numloc] != 0xFFFFFF )
                ((Uint32*)gScreen->pixels)[scrloc] = ((Uint32*)nums->pixels)[numloc];
        
            x0++;
        }
    }
    
    x += 3 + numsWidth[num];
}