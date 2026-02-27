/*
 *  SMenuState.h
 *  Snake
 *
 *  Created by Tyler on 7/20/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *
 *  CHANGELOG:
 *  20Jul06 TDK New Code.
 */

#ifndef SMENUSTATE_H
#define SMENUSTATE_H

#include "SGameEngine.h"
#include "SGameState.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Menu.h"

class SMenuState: public SGameState
{
public:
    void Init( SGameEngine* game );
    void Cleanup();
    
    void Pause();
    void Resume();
    
    void HandleEvents( SGameEngine* game );
    void Update( SGameEngine* game );
    void Draw( SGameEngine* game );
    
    static SMenuState* Instance() { return &snakeMenuState; }

protected:
    SMenuState() {}
	~SMenuState() {}

private:
	void init_menus( SGameEngine* game );
    
	SDL_Surface* bg;

    static SMenuState snakeMenuState;
    enum { MAIN_MENU, OPTIONS_MENU };
    Menu* current_menu;
    
    Menu* main_menu;
    Menu* options_menu;
	Menu* num_players_menu;
};

#endif
