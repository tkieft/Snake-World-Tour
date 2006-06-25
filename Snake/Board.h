/*
 *  Board.h
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  18Jun06 TDK Make WALL_COLOR non static constant (read from level file)
 *  17Jun06 TDK Add ending position constants.
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
#include "SDL_ttf.h"
#include "SnakePlayer.h"

class Board
{
private:
    const static int LEVEL_FLOOR = 0;
    const static int LEVEL_WALL = 1;
    const static int LEVEL_COLLECTIBLE = 5;
    SDL_Color WALL_COLOR;
    SDL_Color FLOOR_COLOR;
    
    int currentLevel;
    int* levelData;
    string levelPath;
    string applePath;
    int* snakeHead;
    int* snakeHeadPosition;
    int collectibles;
    SDL_Surface* apple;
    
    void levelInit( int numSnakes );
    
public:
    /* Class-wide constants */
    const static int TILESIZE = 12;
    const static int LEVELSIZE = 35;
    const static int XLOC = 30;
    const static int YLOC = 30;
    
    /* Constructor and destructor */        
    Board();
    void Cleanup();
    
    /* Methods */
    void Init( string rsrcPath, int numSnakes );
    
    int updatePosition( SnakePlayer* snakes[] );
    void drawLevelPlaying( SDL_Surface* scr, SnakePlayer* snakes[] );
    void drawLevelStart( SDL_Surface* scr );
    void drawSnakeInfo( SDL_Surface* scr, SnakePlayer* snakes[] );
    
    void nextLevel( int numSnakes );
    void restartLevel( int numSnakes );
    bool readCurrentLevel();
    void initCollectibles();
    
private:
    const static int STARTING_POSITION[];
    const static int ENDING_POSITION[];
    
    TTF_Font *levelNumFont;
    SDL_Surface *fontSurface;
    SDL_Color levelNumColor;
    SDL_Color levelNumBG;
};

#endif
