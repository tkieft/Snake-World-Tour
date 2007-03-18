/*
 *  SIntroState.h
 *  Snake
 *
 *  Created by Tyler on 6/21/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  21Jun06 TDK New Code.
 */

#ifndef SINTROSTATE_H
#define SINTROSTATE_H

#include "SDL.h"
#include "SGameEngine.h"
#include "SGameState.h"

class SIntroState: public SGameState
{
public:
    void Init( SGameEngine* game );
    void Cleanup();
    
    void Pause();
    void Resume();
    
    void HandleEvents( SGameEngine* game );
    void Update( SGameEngine* game );
    void Draw( SGameEngine* game );
    
    static SIntroState* Instance() { return &snakeIntroState; }
    
protected:
    SIntroState() {}
	~SIntroState() {}
    
private:
    static SIntroState snakeIntroState;
    SDL_Surface* title;
    SDL_Surface* fader;
    int alpha;
    int startticks;
};

#endif