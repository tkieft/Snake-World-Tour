/*
 *  MenuOption.cpp
 *  Snake
 *
 *  Created by Tyler on 7/20/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGE LOG:
 *  20Jul06 TDK New Code.
 */

#include "MenuOption.h"

MenuOption::MenuOption( string theName, bool isSelectable ) : choices() {
    name = theName;
    selectable = isSelectable;
    num_choices = 0;
    current_choice = 0;
}

void MenuOption::addChoice( string newChoice )
{
    choices[num_choices++] = newChoice;
}

void MenuOption::nextChoice() {
    if( ++current_choice >= num_choices )
        current_choice = 0;
}

void MenuOption::previousChoice() {
    if( --current_choice < 0 )
        current_choice += num_choices;
}

string MenuOption::getCurrentChoice() {
    return choices[current_choice];
}

string MenuOption::getName() {
    return name;
}