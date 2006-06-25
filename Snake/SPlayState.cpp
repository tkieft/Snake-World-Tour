/*
 *  SPlayState.cpp
 *  Snake
 *
 *  Created by Tyler on 6/17/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  15Jun06 TDK gameState variable to hold state.
 *  24Jun06 TDK Move SDL_Flip below Unlock screen.
 *  17Jun06 TDK New Code.
 *
 */

#include "SDL.h"
#include "SPlayState.h"
#include "load_image.h"
#include <iostream>

SPlayState SPlayState::snakePlayState;

SPlayState::SPlayState() : theBoard(), theTimer()
{
    theSnakes[0] = NULL;
    theSnakes[1] = NULL;
}

void SPlayState::Init( SGameEngine* game )
{
    // load up background
    bg = load_image( game->getFileDirectory() + "snake.png" );
    
    // create snake(s)
    SDL_Color c1 = { 0x00, 0x00, 0xA5 };
    SDL_Color c2 = { 0x00, 0x33, 0x22 };
    theSnakes[0] = new SnakePlayer( c1, "Tyler", SnakePlayer::SNAKE_UP );
    if( game->getNumPlayers() == 2 )
        theSnakes[1] = new SnakePlayer( c2, "Brandon", SnakePlayer::SNAKE_DOWN );
    // set up board and timer
    theBoard.Init( game->getFileDirectory(), game->getNumPlayers() );
    theTimer.Init( game->getFileDirectory() );
    
    gameState = LEVEL_START;
}

void SPlayState::Cleanup()
{
    // cleanup members
    theBoard.Cleanup();
    theTimer.Cleanup();
    
    // free the background
    SDL_FreeSurface( bg );   
}

void SPlayState::Pause()
{
    theTimer.pause();
}
void SPlayState::Resume()
{
    theTimer.unpause();
}

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
                        if( gameState == LEVEL_LOST || gameState == LEVEL_WON )
                        {
                            theSnakes[0]->reset( SnakePlayer::SNAKE_UP );
                            if( theSnakes[1] ) theSnakes[1]->reset( SnakePlayer::SNAKE_DOWN );
                        }
                        if( gameState == LEVEL_LOST )
                        {
                            gameState = LEVEL_PLAYING;
                            theBoard.restartLevel( game->getNumPlayers() );
                            theTimer.start();
                            break;
                        }
                        if( gameState == LEVEL_WON ) {
                            gameState = LEVEL_START;
                            theBoard.nextLevel( game->getNumPlayers() );
                            break;
                        }
                        if( gameState == LEVEL_START ) {
                            gameState = LEVEL_PLAYING;
                            theTimer.start();
                        }
                        break;
                    case SDLK_LEFT: case SDLK_DOWN: case SDLK_UP: case SDLK_RIGHT:
                        if( gameState == LEVEL_PLAYING )
                            theSnakes[0]->handleInput( &event );
                        break;
                    case SDLK_a: case SDLK_s: case SDLK_w: case SDLK_d:
                        if( game->getNumPlayers() == 2 && gameState == LEVEL_PLAYING )
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
    if( gameState == LEVEL_PLAYING )
    {
        theSnakes[0]->updateDirection();
        if( theSnakes[1] ) theSnakes[1]->updateDirection();
        int result = theBoard.updatePosition( theSnakes );
        if( result == 1 || result == 2 )
        {
            if( !(theSnakes[ result - 1 ]->die()) ) {
                gameState = GAME_LOST;
                theTimer.stop();
            }
            else {
                gameState = LEVEL_LOST;
                theTimer.stop();
            }
        }
        else if( result == 3 || result == 4 )
        {
            gameState = LEVEL_WON;
            theSnakes[ result-3 ]->win();
            theTimer.stop();
        }
    }
}

void SPlayState::Draw( SGameEngine* game )
{
    SDL_BlitSurface( bg, NULL, game->screen, NULL );

    if( gameState != LEVEL_START ) {      
        theBoard.drawLevelPlaying( game->screen, theSnakes );
        theBoard.drawSnakeInfo( game->screen, theSnakes );
        theTimer.draw( 554, 389, game->screen );
    }
    else {
        theBoard.drawLevelStart( game->screen );
        theBoard.drawSnakeInfo( game->screen, theSnakes );
    }
    
    SDL_Flip( game->screen );
}
