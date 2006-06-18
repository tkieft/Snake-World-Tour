/*
 *  SPlayState.cpp
 *  Snake
 *
 *  Created by Tyler on 6/17/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  17Jun06 TDK New Code.
 *
 */

#include "SDL.h"
#include "SPlayState.h"
#include "load_image.h"

SPlayState SPlayState::snakePlayState;

SPlayState::SPlayState() : SGameState(), theBoard()
{
    theSnakes[0] = NULL;
    theSnakes[1] = NULL;
}

void SPlayState::Init( SGameEngine* game )
{
    // load up background
    bg = load_image( game->getFileDirectory() + "snake.png" );
    
    // create snake(s)
    theSnakes[0] = new SnakePlayer( 0xFFFFFF, "Tyler", SnakePlayer::SNAKE_UP );
    if( game->getNumPlayers() == 2 )
        theSnakes[1] = new SnakePlayer( 0x003322, "Brandon", SnakePlayer::SNAKE_DOWN );
    
    theBoard.Init( game->getFileDirectory(), game->getNumPlayers() );
    drewBackground = false;
    lost = false;
    won = false;
}

void SPlayState::Cleanup()
{
    // free the background
    SDL_FreeSurface( bg );   
}

void SPlayState::Pause() { drewBackground = false; }
void SPlayState::Resume() { return; }

void SPlayState::HandleEvents( SGameEngine* game )
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) )
    {
        switch( event.type )
        {
            case SDL_QUIT:
                game->Quit();
                break;
            
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                        game->Quit();
                        break;
                    case SDLK_SPACE:
                        if( lost || won )
                        {
                            for( int i = 0; i < game->getNumPlayers(); i++ )
                                theSnakes[i]->reset();
                        }
                        if( lost )
                        {
                            lost = false;
                            theBoard.restartLevel( game->getNumPlayers() );
                        }
                        if( won )
                        {
                            won = false;
                            theBoard.nextLevel( game->getNumPlayers() );
                        }
                        break;
                    case SDLK_LEFT: case SDLK_DOWN: case SDLK_UP: case SDLK_RIGHT:
                        theSnakes[0]->handleInput( &event );
                        break;
                    case SDLK_a: case SDLK_s: case SDLK_w: case SDLK_d:
                        if( game->getNumPlayers() == 2)
                            theSnakes[1]->handleInput( &event );
                        break;
                    default: break;
                }
                break;
            
            default:
                break;
        }
    }
}

void SPlayState::Update( SGameEngine* game )
{
    if( !( lost || won ) )
    {
        theSnakes[0]->updateDirection();
        if( theSnakes[1] ) theSnakes[1]->updateDirection();
        int result = theBoard.updatePosition( theSnakes );
        if( result == 1 || result == 2 )
        {
            theSnakes[ result - 1 ]->die();
            lost = true;
        }
        else if( result == 3 || result == 4 )
            won = true;
    }
}

void SPlayState::Draw( SGameEngine* game )
{
    if( !drewBackground )
        SDL_BlitSurface( bg, NULL, game->screen, NULL );
      
    theBoard.draw( game->screen, theSnakes );
        
    if( !drewBackground ) 
    {
        SDL_Flip( game->screen );
        drewBackground = true;
    }
}