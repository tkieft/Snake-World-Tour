/*
 *  Timer.h
 *  Snake
 *
 *  Created by Tyler on 6/19/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGE LOG:
 *  19Jun06 TDK New Code.
 */

#ifndef TIMER_H
#define TIMER_H

#include <string>
#include "SDL.h"
#include "load_image.h"
using std::string;

class Timer
{
private:
    int startTicks;
    int pausedTicks;
    int stoppedTicks;
    
    bool paused;
    bool started;
    bool stopped;
    
    SDL_Surface* nums;
    const static int NUMWIDTH = 30;
    const static int NUMHEIGHT = 40;
    const static int SWIDTH = 400;
    int numsOfs[12];
    int numsWidth[12];
    
    void calcNumSize();

public:
    Timer();
    ~Timer();
    void Init( string pathToResources );
    void draw( int x, int y, SDL_Surface* gScreen );
    void drawOne( int& x, int& y, int num, SDL_Surface* gScreen );
    
    void start();
    void pause();
    void unpause();
    void stop();
    
    int get_ticks();
    bool is_started() { return started; }
    bool is_paused() { return paused; }
    
};

#endif