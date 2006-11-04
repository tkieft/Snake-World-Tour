/*
 *  Menu.cpp
 *  Snake
 *
 *  Created by Tyler on 7/20/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGE LOG:
 *  3Nov06  TDK Reset method.
 *  3Nov06  TDK Fool around with colors.
 *  3Nov06  TDK Draw smaller black rectangle so background is shown.
 *  20Jul06 TDK New Code.
 */

#include "Menu.h"
#include "globals.h"

Menu::Menu( string theTitle, string rsrcPath ) : options() {
    title = theTitle;
    numOptions = 0;
    currentOption = 0;
    
    theFont = TTF_OpenFont( (rsrcPath + "snake.000").c_str(), 25 );
	titleColor.r = 0xB9; titleColor.g = 0x09; titleColor.b = 0x15;
    textColor.r = 0x07; textColor.g = 0x7E; textColor.b = 0x41;
    textSelectedColor.r = 0xFB; textSelectedColor.g = 0xFF; textSelectedColor.b = 0x00;
    bgColor.r = 0x00; bgColor.g = 0x00; bgColor.b = 0x00;
}

Menu::~Menu() {
    for( int i = 0; i < numOptions; i++ )
        delete options[i];
        
    TTF_CloseFont( theFont );
}

void Menu::addOption( string newOption ) {
    options[ numOptions++ ] = new MenuOption( newOption );
}

void Menu::addSelectableOption( string newOption ) {
    options[ numOptions++ ] = new MenuOption( newOption, true );
}

void Menu::addOptionChoice( string optName, string choice ) {
    int opt = -1;
    
    while( options[ ++opt ]->getName() != optName );
    
    options[opt]->addChoice( choice );
}

void Menu::nextOption() {
    if( ++currentOption >= numOptions )
        currentOption = 0;
}

void Menu::previousOption() {
    if( --currentOption < 0 )
        currentOption += numOptions;
}

void Menu::previousChoice() {
    options[currentOption]->previousChoice();
}

void Menu::nextChoice() {
    options[currentOption]->nextChoice();
}

string Menu::getOption() {
    return options[currentOption]->getName();
}

void Menu::reset() {
	currentOption = 0;
}

string Menu::getChoice( string optName )
{
    int opt = -1;
    while( options[++opt]->getName() != optName );
    
    return options[opt]->getCurrentChoice();
}

void Menu::Draw( SGameEngine* game )
{
	SDL_Rect bgrect = { 28, 28, SCREENWIDTH - 28 * 2, SCREENHEIGHT - 28 * 2 };
    SDL_FillRect( game->screen, &bgrect, SDL_MapRGB( game->screen->format, bgColor.r, bgColor.g, bgColor.b ) );
    
    //draw menu title
	fontSurface = TTF_RenderText_Blended( theFont, title.c_str(), titleColor );
	SDL_Rect where = { SCREENWIDTH / 2 - fontSurface->w / 2, 75 };
	SDL_BlitSurface( fontSurface, NULL, game->screen, &where );

	//draw top line
	where.h = 3;
	where.w = fontSurface->w + 8;
	where.x -= 4;
	where.y -= 2;
	SDL_FillRect( game->screen, &where, SDL_MapRGB( game->screen->format, titleColor.r, titleColor.g, titleColor.b ) );

	//draw left line
	where.x -= 3;
	where.h = 6 + fontSurface->h;
	where.w = 3;
	SDL_FillRect( game->screen, &where, SDL_MapRGB( game->screen->format, titleColor.r, titleColor.g, titleColor.b ) );
	
	//draw right line
	where.x += 10 + fontSurface->w;
	SDL_FillRect( game->screen, &where, SDL_MapRGB( game->screen->format, titleColor.r, titleColor.g, titleColor.b ) );
	
	//draw bottom line
	where.x = SCREENWIDTH / 2 - fontSurface->w / 2 - 4;
	where.y += 3 + fontSurface->h;
	where.h = 3;
	where.w = fontSurface->w + 8;
	SDL_FillRect( game->screen, &where, SDL_MapRGB( game->screen->format, titleColor.r, titleColor.g, titleColor.b ) );    
	SDL_FreeSurface( fontSurface );
	
	
    
    int offset = SCREENHEIGHT / 2 - 50 * numOptions / 2;
    for( int i = 0; i < numOptions; i++ ) {
        if( options[i]->isSelectable() )
            drawSelectableOption( game, i, offset );
        else
            drawOption( game, i, offset );
        
        offset += 50;
    }        
}

void Menu::drawSelectableOption( SGameEngine* game, int q, int yofs )
{
    fontSurface = TTF_RenderText_Blended( theFont, (options[q]->getName()).c_str(), textColor );
                
    SDL_Rect where = { SCREENWIDTH / 2 - fontSurface->w / 2, yofs };
    SDL_BlitSurface( fontSurface, NULL, game->screen, &where );
    if( q == currentOption ) {
        where.x -= 20;
        where.y += 12;
        where.w = 12;
        where.h = 12;
        SDL_FillRect( game->screen, &where, SDL_MapRGB( game->screen->format, textSelectedColor.r, textSelectedColor.g, textSelectedColor.b));
    }
    SDL_FreeSurface( fontSurface );
}

void Menu::drawOption( SGameEngine* game, int q, int yofs )
{
    int totalWidth = 0;
    SDL_Surface* fSurfaces[ options[q]->getChoices() + 1 ];
    fSurfaces[0] = TTF_RenderText_Blended( theFont, (options[q]->getName()+":").c_str(), textColor );
    totalWidth += fSurfaces[0]->w + 30;
    for( int i = 0; i < options[q]->getChoices(); i++ ) {
        if( i == options[q]->getCurrentChoiceNum() )
            fSurfaces[i+1] = TTF_RenderText_Blended( theFont, (options[q]->getChoiceWithNum(i)).c_str(), textSelectedColor );
        else
            fSurfaces[i+1] = TTF_RenderText_Blended( theFont, (options[q]->getChoiceWithNum(i)).c_str(), textColor );
        totalWidth += fSurfaces[i+1]->w + 30;
    }
                
    SDL_Rect where = { SCREENWIDTH / 2 - (totalWidth-30) / 2, yofs };
    for( int i = 0; i < options[q]->getChoices() + 1; i++ ){
        SDL_BlitSurface( fSurfaces[i], NULL, game->screen, &where );
        if( q == currentOption && i-1 == options[q]->getCurrentChoiceNum() ) {
            SDL_Rect where2 = where;
            where2.x -= 20;
            where2.y += 12;
            where2.w = 12;
            where2.h = 12;
            SDL_FillRect( game->screen, &where2, SDL_MapRGB( game->screen->format, textSelectedColor.r, textSelectedColor.g, textSelectedColor.b));
        }
        where.x += 30 + fSurfaces[i]->w;
        SDL_FreeSurface( fSurfaces[i] );
    }
    
}