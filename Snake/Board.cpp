/*
 *  Board.cpp
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  16Jun06 TDK Add destructor, initialize and delete levelData, 
                nextLevel(), readCurrentLevel().
 *  16Jun06 TDK Add currentLevel variable.
 *  12Jun06 TDK New Code.
 */

#include <fstream>
#include <cstdlib>
#include <iostream>
using std::ifstream;
using std::ios;

#include "Board.h"
#include "drawfunc.h"
#include "globals.h"
#include "SnakePlayer.h"


Board::Board ( SDL_Surface* sc, string rsrcPath ) : scr( sc ), currentLevel( 1 )
{
    levelPath = rsrcPath + "levels.txt";
    levelData = new int[ LEVELSIZE * LEVELSIZE ];
    readCurrentLevel();
}

Board::~Board() { delete[] levelData; }

void Board::draw( SnakePlayer* snakes[], int numSnakes )
{
    Uint32 color;
    int tile;
    
    if( SDL_MUSTLOCK( scr ) )
        if( SDL_LockSurface( scr ) < 0 )
            return;
    
    for( int y = 0; y < LEVELSIZE; y++ )
        for( int x = 0; x < LEVELSIZE; x++ )
        {
            tile = levelData[ y * LEVELSIZE + x ];
            if( tile == LEVEL_FLOOR )
                color = FLOORCOLOR;
            else if( tile == LEVEL_WALL )
                color = WALLCOLOR;
            else if( tile >= 10 && tile < 400 )
                color = snakes[0]->getColor();
            else if( numSnakes == 2 && tile >= 400 )
                color = snakes[1]->getColor();
                
            drawrect( XLOC + x * TILESIZE, YLOC + y * TILESIZE, TILESIZE, TILESIZE, color, scr);
        }
    if( SDL_MUSTLOCK( scr ) )
        SDL_UnlockSurface( scr );
    
    SDL_UpdateRect( scr, XLOC, YLOC, XLOC - 1 + TILESIZE * LEVELSIZE, YLOC - 1 + TILESIZE * LEVELSIZE );            
}

void Board::nextLevel()
{
    currentLevel++;
    if( ! readCurrentLevel() )
    {
        currentLevel = 1;
        if( ! readCurrentLevel() )
            exit( 1 );
    }
}

bool Board::readCurrentLevel()
{
    ifstream levelFile( levelPath.c_str(), ios::in );
    string line;
    
    if( !levelFile )
        return false;
    
    bool gotNewLevel = false;
    
    while( ! levelFile.eof() )
    {
        std::getline( levelFile, line );
        if( line.find( ( (char) currentLevel ) + ":" ) == 0 )
        {
            gotNewLevel = true;
            break;
        }
    }
    
    if( ! gotNewLevel ) 
        return false;
        
    int currentNum;
    for( int i = 0; i < LEVELSIZE; i++ )
    {
        for( int j = 0; j < LEVELSIZE; j++ )
        {
            levelFile >> currentNum;
            levelData[ i * LEVELSIZE + j ]  = currentNum;
        }
    }        
    
    levelFile.close();
    return true;
}