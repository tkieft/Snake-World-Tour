/*
 *  Board.cpp
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  18Jun06 TDK readCurrentLevel() more efficient, now read wall color.
 *  17Jun06 TDK Eye drawing and apple drawing code.
 *  16Jun06 TDK Collectibles.
 *  16Jun06 TDK Gate closes once snake is out.
 *  16Jun06 TDK Add updatePosition()
 *  16Jun06 TDK Add destructor, initialize and delete levelData, 
 *              nextLevel(), readCurrentLevel().
 *  16Jun06 TDK Add currentLevel variable.
 *  12Jun06 TDK New Code.
 */

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;

#include "Board.h"
#include "drawfunc.h"
#include "globals.h"
#include "load_image.h"

const int Board::STARTING_POSITION[] = { ( LEVELSIZE * (LEVELSIZE - 1) ) + LEVELSIZE / 2, LEVELSIZE / 2 };
const int Board::ENDING_POSITION[] = { Board::STARTING_POSITION[1], Board::STARTING_POSITION[0] };

Board::Board() : currentLevel( 0 ) {}

void Board::Init( string rsrcPath, int numSnakes )
{
    levelPath = rsrcPath + "levels.txt";
    applePath = rsrcPath + "apple.bmp";
    
    levelData = new int[ LEVELSIZE * LEVELSIZE ];
    
    snakeHead = new int[ numSnakes ];
    snakeHeadPosition = new int[ numSnakes ];
    
    apple = load_image( applePath, 0xFF, 0x00, 0xFF );
    
    nextLevel( numSnakes );
}

Board::~Board()
{
    SDL_FreeSurface( apple );
    delete[] levelData;
    delete[] snakeHead;
    delete[] snakeHeadPosition;
}

void Board::draw( SDL_Surface* scr, SnakePlayer* snakes[] )
{
    Uint32 color;
    int tile;
        
    for( int y = 0; y < LEVELSIZE; y++ )
    {
        for( int x = 0; x < LEVELSIZE; x++ )
        {
            tile = levelData[ y * LEVELSIZE + x ];
            if( tile != LEVEL_COLLECTIBLE )
            {
                if( tile == LEVEL_FLOOR )
                    color = FLOOR_COLOR;
                else if( tile == LEVEL_WALL )
                    color = WALL_COLOR;
                else if( tile >= 10 && tile < 400 )
                    color = snakes[0]->getColor();
                else if( snakes[1] && tile >= 400 )
                    color = snakes[1]->getColor();
                
                drawrect( XLOC + x * TILESIZE, YLOC + y * TILESIZE, TILESIZE, TILESIZE, color, scr);
            }
            else
            {
                // cannot blit to locked surface?!
                //SDL_Rect spot;
                //spot.y = YLOC + y * TILESIZE;
                //spot.x = XLOC + x * TILESIZE;
                //if (SDL_BlitSurface(apple, NULL, scr, &spot ) != 0 ) cout << "Failure to blit." << endl;
                SDL_UpdateRect( scr, XLOC + x * TILESIZE, YLOC + y * TILESIZE, XLOC + x * (TILESIZE + 1), YLOC + y * (TILESIZE + 1));
                for( int i = 0; i < TILESIZE; i++ ) 
                    for( int j = 0; j < TILESIZE; j++ )
                        if( ((unsigned int*)apple->pixels)[ i * TILESIZE + j ] != SDL_MapRGB( apple->format, 0xFF, 0x00, 0xFF ) )
                            ((unsigned int*)scr->pixels)[ (YLOC + y * TILESIZE) * scr->pitch / 4 + XLOC + x * TILESIZE + ( i * scr->pitch / 4 ) + j] = ((unsigned int*)apple->pixels)[i * TILESIZE + j];
                        else
                            ((unsigned int*)scr->pixels)[ (YLOC + y * TILESIZE) * scr->pitch / 4 + XLOC + x * TILESIZE + ( i * scr->pitch / 4 ) + j] = FLOOR_COLOR;
            }
        }
    }
            
    // draw snake eyes
    int eyeloc1x, eyeloc1y, eyeloc2x, eyeloc2y;
    for( int i = 0; i < ( snakes[1] ? 2 : 1 ); i++ )
    {
        int headx = snakeHeadPosition[i] % 35 * TILESIZE + XLOC;
        int heady = snakeHeadPosition[i] / 35 * TILESIZE + YLOC;
        switch( snakes[i]->getDirection() )
        {
            case SnakePlayer::SNAKE_UP:
                eyeloc1x = headx + 3; eyeloc1y = heady + 4;
                eyeloc2x = headx + 7; eyeloc2y = heady + 4;
                break;
            case SnakePlayer::SNAKE_DOWN:
                eyeloc1x = headx + 3; eyeloc1y = heady + 8;
                eyeloc2x = headx + 7; eyeloc2y = heady + 8;
                break;
            case SnakePlayer::SNAKE_LEFT:
                eyeloc1x = headx + 4; eyeloc1y = heady + 3;
                eyeloc2x = headx + 4; eyeloc2y = heady + 7;
                break;
            case SnakePlayer::SNAKE_RIGHT:
                eyeloc1x = headx + 8; eyeloc1y = heady + 3;
                eyeloc2x = headx + 8; eyeloc2y = heady + 7;
                break;
            default:
                break;
        }
        drawrect( eyeloc1x, eyeloc1y, 2, 2, 0, scr);
        drawrect( eyeloc2x, eyeloc2y, 2, 2, 0, scr);
    }
    
    // fill in timer box
    drawrect( 474, 406, 575-474, 447-406, 0xFFFFFF, scr);
    //SDL_UpdateRect( scr, XLOC, YLOC, XLOC - 1 + TILESIZE * LEVELSIZE, YLOC - 1 + TILESIZE * LEVELSIZE );            
}

// return 0 if continue, 1 if snake 1 crashed, 2 if snake 2 crashed
// return 3 if snake 1 won, 4 if snake 2 won
int Board::updatePosition( SnakePlayer* snakes[] )
{
    int numSnakes = 1;
    if( snakes[1] ) numSnakes = 2;
    for( int i = 0; i < numSnakes; i++ )
    {
        int direction = snakes[i]->getDirection();
        switch( direction )
        {
            case SnakePlayer::SNAKE_UP:
                if( levelData[ snakeHeadPosition[i] - LEVELSIZE ] != LEVEL_FLOOR )
                {
                    if( levelData[ snakeHeadPosition[i] - LEVELSIZE ] == LEVEL_COLLECTIBLE )
                    {
                        collectibles--;
                        snakes[i]->eat();
                    }
                    else
                        return i+1;
                }
                snakeHeadPosition[i] -= LEVELSIZE;
                levelData[snakeHeadPosition[i]] = ++snakeHead[i];
                break;

            case SnakePlayer::SNAKE_DOWN:
                if( levelData[ snakeHeadPosition[i] + LEVELSIZE ] != LEVEL_FLOOR )
                {
                    if( levelData[ snakeHeadPosition[i] + LEVELSIZE ] == LEVEL_COLLECTIBLE )
                    {
                        collectibles--;
                        snakes[i]->eat();
                    }
                    else
                        return i+1;
                }
                snakeHeadPosition[i] += LEVELSIZE;
                levelData[snakeHeadPosition[i]] = ++snakeHead[i];
                break;
                  
            case SnakePlayer::SNAKE_LEFT:
                if( levelData[ snakeHeadPosition[i] - 1 ] != LEVEL_FLOOR )
                {
                    if( levelData[ snakeHeadPosition[i] - 1 ] == LEVEL_COLLECTIBLE )
                    {
                        collectibles--;
                        snakes[i]->eat();
                    }
                    else
                        return i+1;
                }
                levelData[--snakeHeadPosition[i]] = ++snakeHead[i];
                break;
                    
            case SnakePlayer::SNAKE_RIGHT:
                if( levelData[ snakeHeadPosition[i] + 1 ] != LEVEL_FLOOR )
                {
                    if( levelData[ snakeHeadPosition[i] + 1] == LEVEL_COLLECTIBLE )
                    {
                        collectibles--;
                        snakes[i]->eat();
                    }
                    else
                        return i+1;
                }
                levelData[++snakeHeadPosition[i]] = ++snakeHead[i];
                break;
                        
            default:
                break;
        }
        
        if( !snakes[i]->isGrowing() )
        {
            for( int j = 0; j < LEVELSIZE * LEVELSIZE; j++ )
            {
                if( i == 0 )
                {
                    if( levelData[ j ] == 10 )
                    {
                        levelData[j] = LEVEL_FLOOR;
                        snakeHead[i]--;
                    }
                    else if( levelData[j] > 10 && levelData[j] < 400 )
                        levelData[j]--;
                }
                else
                {
                    if( levelData[ j ] == 400 )
                    {
                        levelData[ j ] = LEVEL_FLOOR;
                        snakeHead[i]--;
                    }
                    else if( levelData[j] > 400 )
                        levelData[j]--;
                }
            }
        }
        
        if( collectibles == 0 )
            if( snakeHeadPosition[i] == ENDING_POSITION[i] )
                return 3 + i;
            else
                levelData[ENDING_POSITION[i]] = LEVEL_FLOOR;
        if( levelData[STARTING_POSITION[i]] == LEVEL_FLOOR && collectibles != 0 )
            levelData[STARTING_POSITION[i]] = LEVEL_WALL;
    }
    return 0;
}
                    

void Board::nextLevel( int numSnakes )
{
    currentLevel++;
    levelInit( numSnakes );
}

void Board::restartLevel( int numSnakes )
{
    levelInit( numSnakes );
}

void Board::levelInit( int numSnakes )
{
    if( ! readCurrentLevel() )
    {
        currentLevel = 1;
        if( ! readCurrentLevel() )
            exit( 1 );
    }
    initCollectibles();
    
    // start snake 1 in middle of bottom, snake 2 in middle of top
    snakeHead[0] = 10;
    snakeHeadPosition[0] = STARTING_POSITION[0];
    levelData[ snakeHeadPosition[0] ] = snakeHead[0];
    if( numSnakes == 2 )
    {
        snakeHead[1] = 400;
        snakeHeadPosition[1] = STARTING_POSITION[1];
        levelData[ snakeHeadPosition[1] ] = snakeHead[1];
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
        //kludgey code
        char ty = '0' + currentLevel;
        if( line.find( ty ) == 0 && line.find( ':' ) == 1 )
        {
            gotNewLevel = true;
            break;
        }
    }
    
    if( ! gotNewLevel ) 
        return false;
        
    for( int i = 0; i < LEVELSIZE * LEVELSIZE; i++ )
        levelFile >> levelData[ i ];
    
    // hex input code
    int col;
    Uint32* myColors[] = { &WALL_COLOR, &FLOOR_COLOR };
    WALL_COLOR = FLOOR_COLOR = 0;
    for( int k = 0; k < 2; k++ )
    {
        cout << k;
        for( int i = 0; i < 6; i++ )
        {
            *(myColors[k]) <<= 4;
            while( 1 )
            {
                col = levelFile.get();
                if( col >= 48 && col <= 57 )
                {
                    col -= 48;
                    break;
                }
                else if( col >= 65 && col <= 70 )
                {
                    col -= 55;
                    break;
                }
                else
                    continue;
            }
        
            *(myColors[k]) |= col;
        }
    }
    
    levelFile.close();
    return true;
}

void Board::initCollectibles()
{
    srand( time( NULL ) );
    collectibles = 10;
    int placement;
    for( int i = 0; i < collectibles; i++ )
    {
        do
        {
            placement = rand() % ( LEVELSIZE * LEVELSIZE );
        }
        while( levelData[placement] != 0 );
        
        levelData[placement] = 5;
    }
}