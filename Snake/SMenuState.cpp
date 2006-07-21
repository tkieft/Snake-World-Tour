/*
 *  SMenuState.cpp
 *  Snake
 *
 *  Created by Tyler on 7/20/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *
 *  CHANGE LOG:
 *  20Jul06 TDK New Code.
 */

#include "SMenuState.h"
#include "SPlayState.h"
#include <iostream>
using std::cout;

SMenuState SMenuState::snakeMenuState;

void SMenuState::Init( SGameEngine* game )
{
    //cout << "Menu State Init";
    init_menus( game );
    current_menu = main_menu;
}

void SMenuState::init_menus( SGameEngine* game ) {
    main_menu = new Menu( "Main Menu", game->getFileDirectory() );
    main_menu->addSelectableOption( "Play" );
    main_menu->addSelectableOption( "Options" );
    main_menu->addSelectableOption( "Quit" );
    
    options_menu = new Menu( "Options", game->getFileDirectory() );
    options_menu->addOption( "screensize" );
    options_menu->addOptionChoice( "screensize", "Windowed" );
    options_menu->addOptionChoice( "screensize", "Fullscreen" );
    
}

void SMenuState::Cleanup()
{
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
                            game->PushState( SPlayState::Instance() );
                        else if( current_menu->getOption() == "Options" )
                            current_menu = options_menu;
                        else
                            game->Quit();
                    }
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
    //cout << "Menu State Draw";
    current_menu->Draw( game );
    SDL_Flip( game->screen );
}