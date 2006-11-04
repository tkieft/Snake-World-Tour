/*
 *  SGameEngine.h
 *  Snake
 *
 *  Created by Tyler on 6/17/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  3Nov06  TDK Add variable to tell if playing or not.
 *  17Jun06 TDK New Code.
 *
 */

#ifndef SGAMEENGINE_H
#define SGAMEENGINE_H

#include "SDL.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class SGameState;

class SGameEngine
{
public:
    void Init( string windowTitle, string d );
    void Cleanup();
    
    void ChangeState( SGameState* state );
    void PushState( SGameState* state );
    void PopState();

    void HandleEvents();
    void Update();
    void Draw();

    bool isRunning() { return gameRunning; }
	
	void startPlaying() { gamePlaying = true; }
	void stopPlaying() { gamePlaying = false; }
	bool isPlaying() { return gamePlaying; }
    
	void Quit() { gameRunning = false; }
    
    SDL_Surface* screen;
    
    int getNumPlayers() { return numPlayers; }
    void setNumPlayers( int n ) { numPlayers = n; }

	int getGameDiff() { return gameDiff; }
	void setGameDiff( int n ) { gameDiff = n; }
    
    string getFileDirectory() { return rsrcdirectory; }
    
private:

    // the stack of states - first in first out
    vector< SGameState* > states;
    bool gameRunning;
	bool gamePlaying;
    int numPlayers;
	int gameDiff;
    string rsrcdirectory;
};

#endif
