/*
 *  SGameEngine.cpp
 *  Snake
 *
 *  Created by Tyler on 6/17/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  17Jun06 TDK New Code.
 */

#include <iostream>
using std::cout;
using std::endl;
#include "SDL.h"
#include "SDL_ttf.h"
#include "SGameEngine.h"
#include "SGameState.h"
#include "globals.h"

void SGameEngine::Init( string windowTitle, string d )
{
    rsrcdirectory = d;
    
    // initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        cout << "Unable to initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    // initialize SDL_TTF
    if( TTF_Init() < 0 )
    {
        cout << "Unable to initialize SDL_ttf";
        exit(1);
    }
    
    // create the screen surface ( 640x480 / 32 bit color )
    screen = SDL_SetVideoMode( SCREENWIDTH, SCREENHEIGHT, SCREENBPP, SDL_SWSURFACE );// | SDL_FULLSCREEN );
    
    if( ! screen )
    {
        cout << "Unable to set 640x480 video: " << SDL_GetError() << endl;
        exit(1);
    }
    
    // set the title bar text
    SDL_WM_SetCaption( windowTitle.c_str(), windowTitle.c_str() );
    
    gameRunning = true;
    numPlayers = 1;
}

void SGameEngine::Cleanup()
{
    // Cleanup all states
    while( ! states.empty() )
    {
        states.back()->Cleanup();
        states.pop_back();
    }
    
    // get rid of SDL & TTF
    TTF_Quit();
    SDL_Quit();
}

void SGameEngine::ChangeState( SGameState* state )
{ 
    // cleanup the current state
    if( !states.empty() )
    {
        states.back()->Cleanup();
        states.pop_back();
    }
    
    // store and init the new state
    states.push_back( state );
    states.back()->Init( this );
}

void SGameEngine::PushState( SGameState* state )
{
    // pause current state
    if( ! states.empty() )
        states.back()->Pause();
    
    // store and init the new state
    states.push_back( state );
    states.back()->Init( this );
}

void SGameEngine::PopState()
{
    // cleanup the current state
    if( ! states.empty() )
    {
        states.back()->Cleanup();
        states.pop_back();
    }
    
    // resume previous state
    if( !states.empty() )
        states.back()->Resume();
}

// let the current state handle events, update itself, and draw
void SGameEngine::HandleEvents() { states.back()->HandleEvents( this ); }
void SGameEngine::Update() { states.back()->Update( this ); }
void SGameEngine::Draw() { states.back()->Draw( this ); }
