/*
 *  Board.h
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  16Jun06 TDK Collectibles.
 *  16Jun06 TDK Add starting position constants.
 *  16Jun06 TDK Add updatePosition().
 *  16Jun06 TDK Add readCurrentLevel() and nextLevel() methods, 
 *              levelData array, destructor.
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
    const static int LEVEL_COLLECTIBLE = 5;
    const static Uint32 WALL_COLOR = 0x003399;
    const static Uint32 FLOOR_COLOR = 0x000000;
    const static Uint32 COLLECTIBLE_COLOR = 0x990000;
    
    SDL_Surface* scr;
    int currentLevel;
    int* levelData;
    string levelPath;
    int* snakeHead;
    int* snakeHeadPosition;
    int collectibles;
    
    void levelInit( int numSnakes );
    
public:
    /* Class-wide constants */
    const static int TILESIZE = 12;
    const static int LEVELSIZE = 35;
    const static int XLOC = 30;
    const static int YLOC = 30;
    
    /* Constructor and destructor */        
    Board( SDL_Surface* sc, string rsrcPath, int numSnakes );
    ~Board();
    
    /* Methods */
    int updatePosition( SnakePlayer* snakes[] );
    void draw( SnakePlayer* snakes[] );
    void nextLevel( int numSnakes );
    void restartLevel( int numSnakes );
    bool readCurrentLevel();
    void initCollectibles();
    
private:
    const static int STARTING_POSITION[];
};

#endif