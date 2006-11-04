/*
 *  SMenuState.cpp
 *  Snake
 *
 *  Created by Tyler on 7/20/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *
 *  CHANGE LOG:
 *  3Nov06  TDK Add draw common background before drawing menu text.
 *  20Jul06 TDK New Code.
 */

#include "SMenuState.h"
#include "SPlayState.h"
#include "globals.h"
#include <iostream>
using std::cout;

SMenuState SMenuState::snakeMenuState;

void SMenuState::Init( SGameEngine* game )
{
	// load up background
    bg = load_image( game->getFileDirectory() + "snake.png" );
	
    //cout << "Menu State Init";
    init_menus( game );
    current_menu = main_menu;
}

void SMenuState::init_menus( SGameEngine* game ) {
    main_menu = new Menu( "Main Menu", game->getFileDirectory() );
	if( game->isPlaying() )
    	main_menu->addSelectableOption( "Resume Game" );
	else
		main_menu->addSelectableOption( "Play" );
    main_menu->addSelectableOption( "Options" );
    main_menu->addSelectableOption( "Quit" );
    
    options_menu = new Menu( "Options", game->getFileDirectory() );
    options_menu->addOption( "Screen Size" );
    options_menu->addOptionChoice( "Screen Size", "Windowed" );
    options_menu->addOptionChoice( "Screen Size", "Fullscreen" );
    options_menu->addSelectableOption( "Save" );
    options_menu->addSelectableOption( "Cancel" );
    
}

void SMenuState::Cleanup()
{
	// free background surface
	SDL_FreeSurface( bg );
	
    delete main_menu;
    delete options_menu;
}

void SMenuState::Pause() {}
void SMenuState::Resume() {}

void SMenuState::HandleEvents( SGameEngine* game )
{
    SDL_Event event;
    while( SDL_PollEvent(&event) )
    {
        if( event.type == SDL_KEYDOWN )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_UP:
                    current_menu->previousOption();
                    break;
                case SDLK_DOWN:
                    current_menu->nextOption();
                    break;
                case SDLK_LEFT:
                    current_menu->previousChoice();
                    break;
                case SDLK_RIGHT:
                    current_menu->nextChoice();
                    break;
                case SDLK_ESCAPE:
                    game->Quit();
                    break;
                case SDLK_RETURN:
                    if( current_menu == main_menu ) {
                        if( current_menu->getOption() == "Play" )
                            game->ChangeState( SPlayState::Instance() );
                        else if( current_menu->getOption() == "Resume Game" )
                            game->PopState();
                        else if( current_menu->getOption() == "Options" )
						{
							options_menu->reset(); //move cursor back to top
                            current_menu = options_menu;
						}
                        else
                            game->Quit();
                    }
                    else {
                        if( current_menu->getOption() == "Cancel" )
						{
							main_menu->reset();
                            current_menu = main_menu;
						}
                        else if( current_menu->getOption() == "Save" ) {
							main_menu->reset();
                            current_menu = main_menu;
                            if( options_menu->getChoice("Screen Size") == "Fullscreen" )
                                SDL_SetVideoMode( SCREENWIDTH, SCREENHEIGHT, SCREENBPP, SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWSURFACE );
                            else
                                SDL_SetVideoMode( SCREENWIDTH, SCREENHEIGHT, SCREENBPP, SDL_SWSURFACE );
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        else if( event.type == SDL_QUIT )
            game->Quit();
    }
}

void SMenuState::Update( SGameEngine* game )
{
}

void SMenuState::Draw( SGameEngine* game )
{
	//Draw common background
	SDL_BlitSurface( bg, NULL, game->screen, NULL );
	
    //cout << "Menu State Draw";
    current_menu->Draw( game );
    SDL_Flip( game->screen );
}