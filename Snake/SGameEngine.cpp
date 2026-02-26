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
    window = SDL_CreateWindow(
        windowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREENWIDTH,
        SCREENHEIGHT,
        SDL_SWSURFACE );

    if( ! window )
    {
        cout << "Unable to set 640x480 video: " << SDL_GetError() << endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if( ! renderer )
    {
        cout << "Unable to create renderer: " << SDL_GetError() << endl;
        exit(1);
    }

    screen = SDL_CreateRGBSurface(0, SCREENWIDTH, SCREENHEIGHT, SCREENBPP,
                                  0x00FF0000,
                                  0x0000FF00,
                                  0x000000FF,
                                  0xFF000000);
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                640, 480);

    if( ! screen )
    {
        cout << "Unable to create surface: " << SDL_GetError() << endl;
        exit(1);
    }

    gameRunning = true;
	gamePlaying = false;
    numPlayers = 1;
	gameDifficulty = 4;
}

void SGameEngine::Cleanup()
{
    // Cleanup all states
    while( ! states.empty() )
    {
        states.back()->Cleanup();
        states.pop_back();
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    texture = NULL;
    screen = NULL;
    renderer = NULL;
    window = NULL;

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
