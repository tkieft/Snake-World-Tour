/*
 *  SMenuState.cpp
 *  Snake
 *
 *  Created by Tyler on 7/20/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *
 *  CHANGE LOG:
 *  15Nov07 TDK Start game while on any menu option.
 *  25Feb06 TDK Fix bug in number of players code.
 *  04Nov06 TDK Add ability to restart game in middle, add difficulty.  
 *  03Nov06 TDK Add draw common background before drawing menu text.
 *  20Jul06 TDK New Code.
 */

#include "SMenuState.h"
#include "SPlayState.h"
#include "SHelpState.h"
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
	main_menu->addSelectableOption( "New Game" );
    main_menu->addSelectableOption( "Options" );
	main_menu->addSelectableOption( "Help" );
    main_menu->addSelectableOption( "Quit" );
    
    options_menu = new Menu( "Options", game->getFileDirectory() );
    options_menu->addOption( "Screen Size" );
    options_menu->addOptionChoice( "Screen Size", "Windowed" );
    options_menu->addOptionChoice( "Screen Size", "Fullscreen" );
    options_menu->addSelectableOption( "Save" );
    options_menu->addSelectableOption( "Cancel" );

	num_players_menu = new Menu( "New Game", game->getFileDirectory() );
	num_players_menu->addOption( "Players" );
	num_players_menu->addOptionChoice( "Players", "1" );
	num_players_menu->addOptionChoice( "Players", "2" );
	num_players_menu->addOption( "Difficulty" );
	num_players_menu->addOptionChoice( "Difficulty", "Easy" );
	num_players_menu->addOptionChoice( "Difficulty", "Normal" );
	num_players_menu->addOptionChoice( "Difficulty", "Expert" );
	num_players_menu->setDefaultChoice( "Difficulty", "Normal" );
	//num_players_menu->addOption( "Snake 1 Name" );
	//num_players_menu->addOptionChoice( "Snake 1 Name", "Tyler" );
	//num_players_menu->addOption( "Snake 2 Name" );
	//num_players_menu->addOptionChoice( "Snake 2 Name", "Brandon" );
	num_players_menu->addSelectableOption( "Play" );
	num_players_menu->addSelectableOption( "Cancel" );
    
}

void SMenuState::Cleanup()
{
	// free background surface
	SDL_FreeSurface( bg );
	
    delete main_menu;
    delete options_menu;
    delete num_players_menu;
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
                        if( current_menu->getOption() == "New Game" )
						{
							num_players_menu->reset();
							current_menu = num_players_menu;
						}
                        else if( current_menu->getOption() == "Resume Game" )
                            game->PopState();
                        else if( current_menu->getOption() == "Options" )
						{
							options_menu->reset(); //move cursor back to top
                            current_menu = options_menu;
						}
						else if( current_menu->getOption() == "Help" )
						{
							game->PushState( SHelpState::Instance() );
						}
                        else
                            game->Quit();
                    }
                    else if( current_menu == num_players_menu ) {
						if( current_menu->getOption() == "Cancel" )
						{
							main_menu->reset();
							current_menu = main_menu;
						}
						else
						{
							if( num_players_menu->getChoice("Players") == "2" )
								game->setNumPlayers(2);
							else
								game->setNumPlayers(1);
							if( num_players_menu->getChoice("Difficulty") == "Easy" )
								game->setGameDifficulty(2);
							else if( num_players_menu->getChoice("Difficulty") == "Expert" )
								game->setGameDifficulty(6);
							
							if( game->isPlaying() )
							{
								game->stopPlaying();
								game->PopState(); //pop the menu state
								game->PopState(); //pop the play state
								game->ChangeState( SPlayState::Instance() );
							}
							else
								game->ChangeState( SPlayState::Instance() );
						}
					}
					else if( current_menu == options_menu ) {
                        if( current_menu->getOption() == "Cancel" )
						{
							main_menu->reset();
                            current_menu = main_menu;
						}
                        else if( current_menu->getOption() == "Save" ) {
							main_menu->reset();
                            current_menu = main_menu;
                            if( options_menu->getChoice("Screen Size") == "Fullscreen" )
                                SDL_SetWindowFullscreen(game->window, SDL_WINDOW_FULLSCREEN);
                            else
                                SDL_SetWindowFullscreen(game->window, 0);
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

    SDL_UpdateTexture(game->texture, NULL, game->screen->pixels, game->screen->pitch);
    SDL_RenderClear(game->renderer);
    SDL_RenderCopy(game->renderer, game->texture, NULL, NULL);
    SDL_RenderPresent(game->renderer);
}
