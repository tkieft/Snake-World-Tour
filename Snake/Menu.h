/*
 *  Menu.h
 *  Snake
 *
 *  Created by Tyler on 7/20/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *
 *  CHANGE LOG:
 *  20Jul06 TDK New Code.
 *
 */

#ifndef MENU_H
#define MENU_H

#include <string>
#include "MenuOption.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SPlayState.h"
#include "SGameEngine.h"

using std::string;

class Menu {
  
private:
    
    MenuOption* options[10];
    string title;
    int numOptions;
    int currentOption;
    
    SDL_Surface *fontSurface;
    TTF_Font *theFont;
	SDL_Color titleColor;
    SDL_Color textColor;
    SDL_Color textSelectedColor;
    SDL_Color bgColor;

	SDL_Surface *apple;
    
    void drawSelectableOption( SGameEngine* game, int q, int yofs );
    void drawOption( SGameEngine* game, int q, int yofs );
    
public:
    Menu( string theTitle, string rsrcPath );
    ~Menu();
    
    void addOption( string newOption );
    void addSelectableOption( string newOption );
    void addOptionChoice( string optName, string choice );
	void setDefaultChoice( string optName, string choice );
    void nextOption();
    void nextChoice();
    void previousOption();
    void previousChoice();
    string getOption();
    string getChoice( string optName );
    void Draw( SGameEngine* game );

	void reset();
    
};

#endif