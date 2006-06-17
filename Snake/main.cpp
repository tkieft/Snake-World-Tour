/* 
 *   Tyler Kieft
 *   June 12, 2006
 *   main.cpp - Initialize SDL
 *
 *   CHANGELOG:
 *   15Jun06 Move render Code to separate function, change init() calling
 *   12Jun06 TDK New Code
 */
   
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "SDL.h"
#include "load_image.h"
#include "globals.h"
#include "Board.h"
#include "SnakePlayer.h"
#include "SGameEngine.h"
#include "SPlayState.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{   
    string rsrcdirectory = (string) *argv;
    rsrcdirectory = rsrcdirectory.substr( 0, rsrcdirectory.length() - 11 ) + "Resources/";
    
    SGameEngine game;
    
    // initialize the engine
    game.Init( "Snake v0.1 beta ©2006 Tyler Kieft", rsrcdirectory );
    
    // load the game
    game.ChangeState( SPlayState::Instance() );
    
    // main loop
    while( game.isRunning() )
    {
        int ticks = SDL_GetTicks();
        
        game.HandleEvents();
        game.Update();
        game.Draw();
        
        while( SDL_GetTicks() - ticks < 1000 / FPS );
    }
    
    // cleanup the engine
    game.Cleanup();
    return 0;
}