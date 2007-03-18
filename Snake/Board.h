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
    const static int LEVEL_WALL2 = 2;
    const static int LEVEL_COLLECTIBLE = 5;
    const static int LEVEL_FLOOR_NO_COLLECTIBLE = 9; //Don't put collectibles here!
    SDL_Color WALL_COLOR;
    SDL_Color WALL2_COLOR;
    SDL_Color FLOOR_COLOR;
    
    int currentLevel;
    int* levelData;
    string levelName;
    string levelLocation;
    
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
    void drawLevelPaused( SDL_Surface* scr );
    void drawGameLost( SDL_Surface* scr );
    void drawSnakeInfo( SDL_Surface* scr, SnakePlayer* snakes[] );
	void drawHelp( SDL_Surface* scr );
    
    void nextLevel( int numSnakes );
    void restartLevel( int numSnakes );
    void setLevel( int level, int numSnakes );
    bool readCurrentLevel();
    void placeCollectible();
    
private:
    const static int STARTING_POSITION[];
    const static int ENDING_POSITION[];
    
    void drawLargeText( const char* text, double yMult, SDL_Surface* scr );
    void drawSmallText( const char* text, SDL_Surface* scr );
    
    TTF_Font *largeFont;
    TTF_Font *smallFont;

    TTF_Font* playerFont[2];
    TTF_Font *levelFont;
    
    SDL_Surface *fontSurface;
    SDL_Color levelNumColor;
    SDL_Color levelNumBG;
};

#endif
