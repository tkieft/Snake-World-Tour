/*
 *  Board.cpp
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  16Jun06 TDK Add updatePosition()
 *  16Jun06 TDK Add destructor, initialize and delete levelData, 
 *              nextLevel(), readCurrentLevel().
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


Board::Board ( SDL_Surface* sc, string rsrcPath, int numSnakes ) : scr( sc ), currentLevel( 1 )
{
    levelPath = rsrcPath + "levels.txt";
    levelData = new int[ LEVELSIZE * LEVELSIZE ];
    readCurrentLevel();
    
    snakeHead = new int[ numSnakes ];
    snakeHeadPosition = new int[ numSnakes ];
    
    // start snake 1 in middle of bottom, snake 2 in middle of top
    snakeHead[0] = 10;
    snakeHeadPosition[0] = (( LEVELSIZE - 1 ) * LEVELSIZE ) + LEVELSIZE / 2;
    levelData[ snakeHeadPosition[0] ] = snakeHead[0];
    if( numSnakes == 2 )
        snakeHead[1] = 400;
        snakeHeadPosition[1] = LEVELSIZE / 2;
        levelData[ snakeHeadPosition[1] ] = snakeHead[1];
}

Board::~Board()
{
    delete[] levelData;
    delete[] snakeHead;
    delete[] snakeHeadPosition;
}

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

// return 0 if all is well, 1 if snake 1 crashed, 2 if snake 2 crashed
int Board::updatePosition( SnakePlayer* snakes[], int numSnakes )
{
    for( int i = 0; i < numSnakes; i++ )
    {
        int direction = snakes[i]->getDirection();
        switch( direction )
        {
            case SnakePlayer::SNAKE_UP:
                if( levelData[ snakeHeadPosition[i] - LEVELSIZE ] != 0 )
                    return i;
                snakeHeadPosition[i] -= LEVELSIZE;
                levelData[snakeHeadPosition[i]] = ++snakeHead[i];
                break;

            case SnakePlayer::SNAKE_DOWN:
                if( levelData[ snakeHeadPosition[i] + LEVELSIZE ] != 0 )
                    return i;
                snakeHeadPosition[i] += LEVELSIZE;
                levelData[snakeHeadPosition[i]] = ++snakeHead[i];
                break;
                  
            case SnakePlayer::SNAKE_LEFT:
                if( levelData[ snakeHeadPosition[i] - 1 ] != 0 )
                    return i;
                levelData[--snakeHeadPosition[i]] = ++snakeHead[i];
                break;
                    
            case SnakePlayer::SNAKE_RIGHT:
                if( levelData[ snakeHeadPosition[i] + 1 ] != 0 )
                    return i;
                levelData[++snakeHeadPosition[i]] = ++snakeHead[i];
                break;
                        
            default:
                break;
        }
        
        bool growth = snakes[i]->isGrowing();
        
        for( int j = 0; j < LEVELSIZE * LEVELSIZE; j++ )
        {
            if( i == 0 && !growth )
            {
                if( levelData[ j ] == 10 )
                {
                    levelData[j] = 0;
                    snakeHead[i]--;
                }
                else if( levelData[j] > 10 && levelData[j] < 400 )
                    levelData[j]--;
            }
            else
            {
                if( levelData[ j ] == 400 && !growth )
                {
                    levelData[ j ] = 0;
                    snakeHead[i]--;
                }
                else if( levelData[j] > 400 )
                    levelData[j]--;
            }
        }
    }
    return 0;
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