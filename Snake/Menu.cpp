/*
 *  Menu.cpp
 *  Snake
 *
 *  Created by Tyler on 7/20/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGE LOG:
 *  20Jul06 TDK New Code.
 */

#include "Menu.h"
#include "globals.h"

Menu::Menu( string theTitle, string rsrcPath ) : options() {
    title = theTitle;
    numOptions = 0;
    currentOption = 0;
    
    theFont = TTF_OpenFont( (rsrcPath + "snake.000").c_str(), 25 );
    textColor.r = 0xFF; textColor.g = 0x00; textColor.b = 0x00;
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

string Menu::getChoice( string optName )
{
    int opt = -1;
    while( options[++opt]->getName() != optName );
    
    return options[opt]->getCurrentChoice();
}

void Menu::Draw( SGameEngine* game )
{
    SDL_FillRect( game->screen, NULL, SDL_MapRGB( game->screen->format, bgColor.r, bgColor.g, bgColor.b ) );
    
    //draw menu title
    fontSurface = TTF_RenderText_Shaded( theFont, title.c_str(), textColor, bgColor );
    SDL_Rect where = { SCREENWIDTH / 2 - fontSurface->w / 2, 20 };
    SDL_BlitSurface( fontSurface, NULL, game->screen, &where );
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
    fontSurface = TTF_RenderText_Shaded( theFont, (options[q]->getName()).c_str(), textColor, bgColor );
                
    SDL_Rect where = { SCREENWIDTH / 2 - fontSurface->w / 2, yofs };
    SDL_BlitSurface( fontSurface, NULL, game->screen, &where );
    if( q == currentOption ) {
        where.x -= 20;
        where.y += 12;
        where.w = 12;
        where.h = 12;
        SDL_FillRect( game->screen, &where, SDL_MapRGB( game->screen->format, textColor.r, textColor.g, textColor.b));
    }
    SDL_FreeSurface( fontSurface );
}

void Menu::drawOption( SGameEngine* game, int q, int yofs )
{
    int totalWidth = 0;
    SDL_Surface* fSurfaces[ options[q]->getChoices() ];
    for( int i = 0; i < options[q]->getChoices(); i++ ) {
        fSurfaces[i] = TTF_RenderText_Shaded( theFont, (options[q]->getChoiceWithNum(i)).c_str(), textColor, bgColor);
        totalWidth += fSurfaces[i]->w + 30;
    }
                
    SDL_Rect where = { SCREENWIDTH / 2 - totalWidth / 2, yofs };
    for( int i = 0; i < options[q]->getChoices(); i++ ){
        SDL_BlitSurface( fSurfaces[i], NULL, game->screen, &where );
        if( q == currentOption && i == options[q]->getCurrentChoiceNum() ) {
            SDL_Rect where2 = where;
            where2.x -= 20;
            where2.y += 12;
            where2.w = 12;
            where2.h = 12;
            SDL_FillRect( game->screen, &where2, SDL_MapRGB( game->screen->format, textColor.r, textColor.g, textColor.b));
        }
        where.x += 30 + fSurfaces[i]->w;
        SDL_FreeSurface( fSurfaces[i] );
    }
    
}