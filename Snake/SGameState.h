/*
 *  SGameState.h
 *  Snake
 *
 *  Created by Tyler on 6/17/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *  
 *  CHANGELOG:
 *  17Jun06 TDK New Code.
 */

#ifndef SGAMESTATE_H
#define SGAMESTATE_H

#include "SGameEngine.h"

class SGameState
{
public:
    virtual void Init( SGameEngine* game ) = 0;
    virtual void Cleanup() = 0;
    
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleEvents( SGameEngine* game ) = 0;
    virtual void Update( SGameEngine* game ) = 0;
    virtual void Draw( SGameEngine* game ) = 0;
    
    
protected:
    SGameState() { }

};

#endif
