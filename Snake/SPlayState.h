/*
 *  SPlayState.h
 *  Snake
 *
 *  Created by Tyler on 6/17/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  17Jun06 TDK New Code.
 *
 */

#ifndef SPLAYSTATE_H
#define SPLAYSTATE_H

#include "SDL.h"
#include "SGameEngine.h"
#include "SGameState.h"
#include "SnakePlayer.h"
#include "Board.h"

class SPlayState: public SGameState
{
public:
    void Init( SGameEngine* game );
    void Cleanup();
    
    void Pause();
    void Resume();
    
    void HandleEvents( SGameEngine* game );
    void Update( SGameEngine* game );
    void Draw( SGameEngine* game );
    
    static SPlayState* Instance() { return &snakePlayState; }
    bool lost;
    bool won;
    
    SnakePlayer* theSnakes[2];
    Board theBoard;

protected:
    SPlayState();
    
private:
    static SPlayState snakePlayState;
    SDL_Surface* bg;
    int drewBackground;

};

#endif