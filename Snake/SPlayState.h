/*
 *  SPlayState.h
 *  Snake
 *
 *  Created by Tyler on 6/17/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  25Jun06 TDK Change state to enum.
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
#include "Timer.h"

class SPlayState: public SGameState
{
private:
    enum State { LEVEL_START, LEVEL_PLAYING, LEVEL_WON, LEVEL_LOST, GAME_LOST };
    State gameState;
public:
    void Init( SGameEngine* game );
    void Cleanup();
    
    void Pause();
    void Resume();
    
    void HandleEvents( SGameEngine* game );
    void Update( SGameEngine* game );
    void Draw( SGameEngine* game );
    
    static SPlayState* Instance() { return &snakePlayState; }

protected:
    SPlayState();
    
private:
    static SPlayState snakePlayState;

    SDL_Surface* bg;

    SnakePlayer* theSnakes[2];
    Board theBoard;
    Timer theTimer;

};

#endif
