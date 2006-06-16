/*
 *  Board.h
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  16Jun06 TDK Add readCurrentLevel() and nextLevel() methods, 
                levelData array, destructor.
 *  16Jun06 TDK Add currentLevel variable.
 *  12Jun06 TDK New Code.
 */

#ifndef BOARD_H
#define BOARD_H

#include <string>
using std::string;

#include "SDL.h"
#include "SnakePlayer.h"

class Board
{
private:
    const static int LEVEL_FLOOR = 0;
    const static int LEVEL_WALL = 1;
    const static Uint32 WALLCOLOR = 0xCC0000;
    const static Uint32 FLOORCOLOR = 0x0000CC;
    
    SDL_Surface* scr;
    int currentLevel;
    int* levelData;
    string levelPath;
    
public:
    /* Class-wide constants */
    const static int TILESIZE = 12;
    const static int LEVELSIZE = 35;
    const static int XLOC = 30;
    const static int YLOC = 30;
    
    /* Constructor and destructor */        
    Board( SDL_Surface* sc, string rsrcPath );
    ~Board();
    
    /* Methods */
    void draw( SnakePlayer* snakes[], int numSnakes );
    void nextLevel();
    bool readCurrentLevel();
};

#endif