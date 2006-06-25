/*
 *  Timer.h
 *  Snake
 *
 *  Created by Tyler on 6/19/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGE LOG:
 *  25Jun06 TDK Change state to enumeration.
 *  19Jun06 TDK New Code.
 */

#ifndef TIMER_H
#define TIMER_H

#include <string>
#include "SDL.h"
#include "SDL_TTF.h"
#include "load_image.h"
using std::string;

class Timer
{
private:
    int startTicks;
    int pausedTicks;
    int stoppedTicks;
    
    enum State { RUNNING, PAUSED, STOPPED };

    State timerState;    

public:
    Timer();
    void Init( string pathToResources );
    void Cleanup();

    void draw( int x, int y, SDL_Surface* gScreen );
    
    void start();
    void pause();
    void unpause();
    void stop();
    
    int get_ticks();
    bool is_running() { return timerState == RUNNING; }
    bool is_paused() { return timerState == PAUSED; }
    bool is_stopped() { return timerState == STOPPED; }
    
private:
    TTF_Font *timerFont;
    SDL_Surface *timerSurface;
    SDL_Color timerColor;
    SDL_Color timerBG;
    
};

#endif
