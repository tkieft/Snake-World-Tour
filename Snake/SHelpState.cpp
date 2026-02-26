/*
 *	SHelpState.cpp
 *	Snake
 *
 *	Created by Tyler on 6/13/07
 *  Copyright 2007 Tyler Kieft. All rights reserved.
 *
 *	CHANGELOG:
 *  13Jun07 TDK New Code.
 *
 */

#include "SHelpState.h"
#include "globals.h"
#include "load_image.h"
#include <string>

using std::string;

SHelpState SHelpState::snakeHelpState;

void SHelpState::Init( SGameEngine* game ) {
	// load up background
    bg = load_image( game->getFileDirectory() + "snake.png" );

	titleFont = TTF_OpenFont( ( game->getFileDirectory() + "snake.000").c_str(), 30 );
	textFont = TTF_OpenFont( ( game->getFileDirectory() + "snake.000").c_str(), 18 );

	bgColor.r = 0x00; bgColor.g = 0x00; bgColor.b = 0x00;
	titleColor1.r = 0xB9; titleColor1.g = 0x09; titleColor1.b = 0x15;
	titleColor2.r = 0x07; titleColor2.g = 0x7E; titleColor2.b = 0x41;
	titleColor3.r = 0xDD; titleColor3.g = 0xDD; titleColor3.b = 0xDD;
	textColor.r = 0x00; textColor.g = 0x88; textColor.b = 0x00;
}

void SHelpState::Cleanup() {
	SDL_FreeSurface( bg );
	TTF_CloseFont( titleFont );
	TTF_CloseFont( textFont );
}

void SHelpState::Pause() {}
void SHelpState::Resume() {}

void SHelpState::HandleEvents( SGameEngine* game ) {
	SDL_Event event;
	
	while( SDL_PollEvent( &event ) ) {
		if( event.type == SDL_KEYDOWN ) {
			game->PopState();
		}
		else if( event.type == SDL_QUIT ) {
			game->Quit();
		}
	}
}

void SHelpState::Update( SGameEngine* game ) {}

void SHelpState::Draw( SGameEngine* game ) {
    SDL_BlitSurface( bg, NULL, game->screen, NULL );

    SDL_Rect bgrect = { 28, 28, SCREENWIDTH - 28 * 2, SCREENHEIGHT - 28 * 2 };
    SDL_FillRect( game->screen, &bgrect, SDL_MapRGB( game->screen->format, bgColor.r, bgColor.g, bgColor.b ) );

    // Render Game Title

    fontSurface = TTF_RenderText_Blended( titleFont, "Snake", titleColor1 );
    SDL_Rect where = { 40, SCREENHEIGHT - 2 * fontSurface->h - 30 };
    SDL_BlitSurface( fontSurface, NULL, game->screen, &where );
    SDL_FreeSurface( fontSurface );

    fontSurface = TTF_RenderText_Blended( titleFont, "World Tour", titleColor2 );
    where.x = 60; where.y += 30;
    SDL_BlitSurface( fontSurface, NULL, game->screen, &where );
    SDL_FreeSurface( fontSurface );

    // Draw Help Title

    fontSurface = TTF_RenderText_Blended( titleFont, "Help", titleColor3 );
    where.x = SCREENWIDTH / 2 - fontSurface->w / 2; where.y = 40;
    SDL_BlitSurface( fontSurface, NULL, game->screen, &where );
    SDL_FreeSurface( fontSurface );

    // Draw Help Text

    string texts[] = { "Control your snake using the",
        "arrow keys on the keyboard.",
        "Don't crash into the walls or",
        "yourself!",
        "There are 10 levels, and you",
        "must devour ten apples on each",
        "level to advance to the next.",
        "Finish each level as fast as you",
        "can to score more points!" };

    where.x = 40; where.y += 40;
    for( int i = 0; i <= 8; i++ ) {
        fontSurface = TTF_RenderText_Blended( textFont, texts[i].c_str(), titleColor3 );
        where.y += fontSurface->h;
        SDL_BlitSurface( fontSurface, NULL, game->screen, &where );
        SDL_FreeSurface( fontSurface );

        if( i == 3 )
            where.y += 10;
        else if ( i == 6 )
            where.y += 10;
    }

    string texts2[] = { "Two Player:",
        "Use w,s,a,d to move.",
        "Players must race to see",
        "who can eat the most",
        "apples without crashing",
        "into each other!"
    };

    where.x = 360; where.y = 80;
    for( int i = 0; i <= 5; i++ ) {
        fontSurface = TTF_RenderText_Blended( textFont, texts2[i].c_str(), titleColor3 );
        where.y += fontSurface->h;
        SDL_BlitSurface( fontSurface, NULL, game->screen, &where );
        SDL_FreeSurface( fontSurface );

        if( i == 1 )
            where.y += 10;
    }



    SDL_UpdateTexture(game->texture, NULL, game->screen->pixels, game->screen->pitch);
    SDL_RenderClear(game->renderer);
    SDL_RenderCopy(game->renderer, game->texture, NULL, NULL);
    SDL_RenderPresent(game->renderer);
}
