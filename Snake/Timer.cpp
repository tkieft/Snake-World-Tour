/*
 *  NumberDrawer.cpp
 *  Snake
 *
 *  Created by Tyler on 6/19/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  25Jun06 TDK Change timerState to enum.
 *  24Jun06 TDK Don't use stupid number bitmap.
 *  19Jun06 TDK New Code.
 */

#include "Timer.h"
#include <iostream>

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    stoppedTicks = 0;
    timerState = STOPPED;    
}

void Timer::Init( string pathToResources )
{
    timerFont = TTF_OpenFont( (pathToResources + "snake.000").c_str(), 25 );
    if( !timerFont )
        exit(1);

    // set timer font color, background color
    timerBG.r = timerBG.b = timerBG.g = 0;
    timerColor.r = 0xEF; timerColor.g = 0x8A; timerColor.b = 0x01;
}

void Timer::Cleanup()
{
    TTF_CloseFont( timerFont );
}

void Timer::start()
{
    timerState = RUNNING;
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    stoppedTicks = SDL_GetTicks();
    timerState = STOPPED;
}

int Timer::get_ticks()
{
    if( is_running() )
        return SDL_GetTicks() - startTicks;

    else if( is_paused() )
        return pausedTicks;
    
    else if( is_stopped() )
        return stoppedTicks - startTicks;

	// get rid of compiler warning
	return 0;
}

void Timer::pause()
{
    if( is_running() )
    {
        timerState = PAUSED;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if( is_paused() )
    {
        timerState = RUNNING;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

void Timer::draw( int x, int y, SDL_Surface* gScreen )
{
    char min = get_ticks() / 1000 / 60 + 48;
    char s1 = (( get_ticks() / 1000 ) % 60 ) / 10 + 48;
    char s2 = (( get_ticks() / 1000 ) % 60 ) % 10 + 48;
    char currentTime[] = { min, ':', s1, s2, '\0' };
    timerSurface = TTF_RenderText_Shaded( timerFont, currentTime, timerColor, timerBG );
    SDL_Rect timerRect; timerRect.x = x; timerRect.y = y;
    SDL_BlitSurface( timerSurface, NULL, gScreen, &timerRect );
    SDL_FreeSurface( timerSurface );
}
