/*
 *  SIntroState.cpp
 *  Snake
 *
 *  Created by Tyler on 6/21/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGE LOG:
 *  21Jun06 TDK New Code.
 */

#include "SIntroState.h"
#include "SPlayState.h"
#include "load_image.h"

SIntroState SIntroState::snakeIntroState;

void SIntroState::Init( SGameEngine* game )
{
    title = load_image( game->getFileDirectory() + "snaketitle.png" );
    //start off transparent, fade to black
    alpha = SDL_ALPHA_OPAQUE;
    fader = SDL_CreateRGBSurface( 0, title->w, title->h,
                                  title->format->BitsPerPixel,
                                  title->format->Rmask, title->format->Gmask,
                                  title->format->Bmask, title->format->Amask );
    
    SDL_FillRect( fader, NULL, SDL_MapRGB( title->format, 0, 0, 0 ));
    SDL_SetAlpha( fader, SDL_SRCALPHA | SDL_RLEACCEL, alpha );
}

void SIntroState::Cleanup()
{
    SDL_FreeSurface( title );
    SDL_FreeSurface( fader );
}

void SIntroState::Pause() {}
void SIntroState::Resume() {}

void SIntroState::HandleEvents( SGameEngine* game )
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_KEYDOWN )
        {
            if( event.key.keysym.sym == SDLK_ESCAPE )
                game->Quit();
            if( event.key.keysym.sym == SDLK_9 )
            {
                game->ChangeState( SPlayState::Instance() );
                return;
            }
        }
        else if( event.type == SDL_QUIT )
            game->Quit();
    }
}

void SIntroState::Update( SGameEngine* game )
{
    alpha -= 10;
    if( alpha < SDL_ALPHA_TRANSPARENT)
    {
        alpha = 0;
        
        if( ! startticks )
            startticks = SDL_GetTicks();
        else if( SDL_GetTicks() - startticks > 3000 )
        {
            game->ChangeState( SPlayState::Instance() );
            return;
        }
    }
    
    SDL_SetAlpha( fader, SDL_SRCALPHA | SDL_RLEACCEL, alpha );
}

void SIntroState::Draw( SGameEngine* game )
{
    SDL_BlitSurface( title, NULL, game->screen, NULL );
    if( alpha )
        SDL_BlitSurface( fader, NULL, game->screen, NULL );
    
    SDL_UpdateRect( game->screen, 0, 0, 0, 0 );
}