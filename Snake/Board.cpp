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
    
    mediumFont = TTF_OpenFont( (rsrcPath + "snake.000").c_str(), 25 );
    smallFont = TTF_OpenFont( (rsrcPath + "snake.000").c_str(), 18 );
    largeFont = TTF_OpenFont( (rsrcPath + "snake.000").c_str(), 34 );
    if( !mediumFont || !smallFont || !largeFont )
        exit(1);
    
    levelNumColor.r = 0xEF; levelNumColor.g = 0x8A; levelNumColor.b = 0x01;
    levelNumBG.r = levelNumBG.b = levelNumBG.g = 0;

    nextLevel( numSnakes );
}

void Board::Cleanup()
{
    SDL_FreeSurface( apple );
    TTF_CloseFont( smallFont );
    TTF_CloseFont( mediumFont );
    TTF_CloseFont( largeFont );
    delete[] levelData;
    delete[] snakeHead;
    delete[] snakeHeadPosition;
}

void Board::drawLevelPlaying( SDL_Surface* scr, SnakePlayer* snakes[] )
{
    if( SDL_MUSTLOCK( scr ) )
    {
        if( SDL_LockSurface( scr ) < 0 )
            return;
    }
    
    SDL_Color color;
    int tile;
        
    for( int y = 0; y < LEVELSIZE; y++ )
    {
        for( int x = 0; x < LEVELSIZE; x++ )
        {
            tile = levelData[ y * LEVELSIZE + x ];
            if( tile != LEVEL_COLLECTIBLE )
            {
                if( tile == LEVEL_FLOOR || tile == LEVEL_FLOOR_NO_COLLECTIBLE )
                    color = FLOOR_COLOR;
                else if( tile == LEVEL_WALL )
                    color = WALL_COLOR;
                else if( tile >= 10 && tile < 400 )
                    color = snakes[0]->getColor();
                else if( snakes[1] && tile >= 400 )
                    color = snakes[1]->getColor();
                
                drawrect( XLOC + x * TILESIZE, YLOC + y * TILESIZE,
                    TILESIZE, TILESIZE,
                    SDL_MapRGB( scr->format, color.r, color.g, color.b), scr);
            }
            else
            {
                // cannot blit to locked surface?!
                //SDL_Rect spot;
                //spot.y = YLOC + y * TILESIZE;
                //spot.x = XLOC + x * TILESIZE;
                //if (SDL_BlitSurface(apple, NULL, scr, &spot ) != 0 ) cout << "Failure to blit." << endl;
                for( int i = 0; i < TILESIZE; i++ ) 
                    for( int j = 0; j < TILESIZE; j++ )
                        if( ((unsigned int*)apple->pixels)[ i * TILESIZE + j ] != SDL_MapRGB( apple->format, 0xFF, 0x00, 0xFF ) )
                            ((unsigned int*)scr->pixels)[ (YLOC + y * TILESIZE) * scr->pitch / 4 + XLOC + x * TILESIZE + ( i * scr->pitch / 4 ) + j] = ((unsigned int*)apple->pixels)[i * TILESIZE + j];
                        else
                            ((unsigned int*)scr->pixels)[ (YLOC + y * TILESIZE) * scr->pitch / 4 + XLOC + x * TILESIZE + ( i * scr->pitch / 4 ) + j] = SDL_MapRGB( scr->format, FLOOR_COLOR.r, FLOOR_COLOR.g, FLOOR_COLOR.b );
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
    
    if( SDL_MUSTLOCK( scr ) ) SDL_UnlockSurface( scr );

}

void Board::drawLargeText( const char* text, double yMult, SDL_Surface* scr )
{
    fontSurface = TTF_RenderText_Shaded( largeFont, text, WALL_COLOR, FLOOR_COLOR );
    SDL_Rect where = { XLOC + ( TILESIZE * LEVELSIZE ) / 2 - fontSurface->w / 2, ( scr->h / 2 ) + ( fontSurface->h * yMult ) };
    SDL_BlitSurface( fontSurface, NULL, scr, &where );
    SDL_FreeSurface( fontSurface );
}

void Board::drawSmallText( const char* text, SDL_Surface* scr )
{
    fontSurface = TTF_RenderText_Shaded( smallFont, text, WALL_COLOR, FLOOR_COLOR );
    SDL_Rect where = { XLOC + ( TILESIZE * LEVELSIZE ) / 2 - fontSurface->w / 2, YLOC + TILESIZE * LEVELSIZE - fontSurface->h };
    SDL_BlitSurface( fontSurface, NULL, scr, &where );
    SDL_FreeSurface( fontSurface );
}

void Board::drawLevelStart( SDL_Surface* scr )
{
    SDL_Rect boardSurface = { XLOC, YLOC, TILESIZE * LEVELSIZE, TILESIZE * LEVELSIZE };
    SDL_FillRect( scr, &boardSurface, SDL_MapRGB( scr->format, FLOOR_COLOR.r, FLOOR_COLOR.g, FLOOR_COLOR.b ) );
    
    char levelText[] = { 'L', 'e', 'v', 'e', 'l', ' ', ((char) currentLevel ) + 48, '\0' };
    drawLargeText( levelText, (-1.5), scr );
    drawLargeText( levelName.c_str(), (-.5), scr );
    drawLargeText( levelLocation.c_str(), .5, scr );

    drawSmallText( "Press space to begin", scr );
}

void Board::drawLevelPaused( SDL_Surface* scr )
{
    SDL_Rect boardSurface = { XLOC, YLOC, TILESIZE * LEVELSIZE, TILESIZE * LEVELSIZE };
    SDL_FillRect( scr, &boardSurface, SDL_MapRGB( scr->format, FLOOR_COLOR.r, FLOOR_COLOR.g, FLOOR_COLOR.b ) );
    
    drawLargeText( "* PAUSED *", -.5, scr );
    drawSmallText( "Press 'p' to continue playing", scr );
}

void Board::drawGameLost( SDL_Surface* scr )
{
    SDL_Rect boardSurface = { XLOC, YLOC, TILESIZE * LEVELSIZE, TILESIZE * LEVELSIZE };
    SDL_FillRect( scr, &boardSurface, SDL_MapRGB( scr->format, FLOOR_COLOR.r, FLOOR_COLOR.g, FLOOR_COLOR.b ) );
    
    drawLargeText( "GAME OVER", -.5, scr );
    drawSmallText( "Press space to play again", scr );
}


void Board::drawSnakeInfo( SDL_Surface* scr, SnakePlayer* snakes[] )
{
    // draw level number
    char levelString[] = { ((char) currentLevel) + 48, '\0' };
    fontSurface = TTF_RenderText_Shaded( mediumFont, levelString, levelNumColor, levelNumBG );
    SDL_Rect levRect = { 554, 414 };
    SDL_BlitSurface( fontSurface, NULL, scr, &levRect );
    SDL_FreeSurface( fontSurface );
    
    // draw player score and lives
    for( int p = 0; p < 2; p++ )
    {
        if( !snakes[p] ) break;
        char playerLives[] = { 'L', 'i', 'v', 'e', 's', ':', ((char) snakes[p]->getLives()) + 48, '\0' };
        int score = snakes[p]->getScore();
        char* playerScore = scoreToChar( score );
        fontSurface = TTF_RenderText_Shaded( mediumFont, playerLives, snakes[p]->getColor(), levelNumBG );
        SDL_Rect p1 = { 475, 150 + p*100 };
        SDL_BlitSurface( fontSurface, NULL, scr, &p1 );
        SDL_FreeSurface( fontSurface );
        fontSurface = TTF_RenderText_Shaded( mediumFont, playerScore, snakes[p]->getColor(), levelNumBG );
        SDL_Rect p2 = { 475, 180 + p*100 };
        SDL_BlitSurface( fontSurface, NULL, scr, &p2 );
        SDL_FreeSurface( fontSurface );
        delete[] playerScore;        
    }
    
}

// return 0 if continue, 1 if snake 1 crashed, 2 if snake 2 crashed
// return 3 if snake 1 won, 4 if snake 2 won
int Board::updatePosition( SnakePlayer* snakes[] )
{
    int numSnakes = 1;
    if( snakes[1] ) numSnakes = 2;
    int nextPos;
    for( int i = 0; i < numSnakes; i++ )
    {
        int direction = snakes[i]->getDirection();
        switch( direction )
        {
            case SnakePlayer::SNAKE_UP:
                nextPos = levelData[ snakeHeadPosition[i]  - LEVELSIZE ];
                if( nextPos != LEVEL_FLOOR && nextPos != LEVEL_FLOOR_NO_COLLECTIBLE )
                {
                    if( nextPos == LEVEL_COLLECTIBLE )
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
                nextPos = levelData[ snakeHeadPosition[i] + LEVELSIZE ];
                if( nextPos != LEVEL_FLOOR && nextPos != LEVEL_FLOOR_NO_COLLECTIBLE)
                {
                    if( nextPos == LEVEL_COLLECTIBLE )
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
                nextPos = levelData[ snakeHeadPosition[i] - 1 ];
                if( nextPos != LEVEL_FLOOR && nextPos != LEVEL_FLOOR_NO_COLLECTIBLE )
                {
                    if( nextPos == LEVEL_COLLECTIBLE )
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
                nextPos = levelData[ snakeHeadPosition[i] + 1 ];
                if( nextPos != LEVEL_FLOOR && nextPos != LEVEL_FLOOR_NO_COLLECTIBLE )
                {
                    if( nextPos == LEVEL_COLLECTIBLE )
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
        
        // won the level
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

void Board::setLevel( int level, int numSnakes )
{
    currentLevel = level;
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
    
    getline( levelFile, levelName );
    getline( levelFile, levelLocation );
        
    for( int i = 0; i < LEVELSIZE * LEVELSIZE; i++ )
        levelFile >> levelData[ i ];
    
    // hex input code
    Uint8 col;
    Uint8 readColor;
    SDL_Color* myColors[] = { &WALL_COLOR, &FLOOR_COLOR };
    
    for( int k = 0; k < 2; k++ )
    {
        //cout << k;
        for( int i = 0; i < 3; i++ )
        {
            col = 0;
            for( int j = 0; j < 2; j++ )
            {
                col <<= 4;
                while( 1 )
                {
                    readColor = levelFile.get();
                    if( readColor >= 48 && readColor <= 57 )
                    {
                        readColor -= 48;
                        break;
                    }
                    else if( readColor >= 65 && readColor <= 70 )
                    {
                        readColor -= 55;
                        break;
                    }
                    else
                        continue;
                }       
                col |= readColor;
            }
            switch( i )
            {
                case 0: myColors[k]->r = col; break;
                case 1: myColors[k]->g = col; break;
                case 2: myColors[k]->b = col; break;
                default: break;
            }
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
        while( levelData[placement] != LEVEL_FLOOR );
        
        levelData[placement] = 5;
    }
}
