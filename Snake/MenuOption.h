/*
 *  MenuOption.h
 *  Snake
 *
 *  Created by Tyler on 7/20/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGE LOG:
 *  20Jul06 TDK New Code.
 */


#ifndef MENUOPTION_H
#define MENUOPTION_H

#include <string>

using std::string;

class MenuOption
{
    string name;
    string choices[10];
    int num_choices;
    int current_choice;
    
    bool selectable;
    
public:
    MenuOption( string theName, bool isSelectable = false );
    void addChoice( string newChoice );
    void nextChoice();
    void previousChoice();
    bool isSelectable() { return selectable; }
    string getCurrentChoice();
    int getCurrentChoiceNum() { return current_choice; }
    string getChoiceWithNum( int num ) { return choices[num]; }
    int getChoices() { return num_choices; }
    string getName();
};

#endif