/* 
 *   Tyler Kieft
 *   June 12, 2006
 *   main.cpp - Initialize SDL
 *
 *   CHANGELOG:
 *   17Jun06 Massive architectural changes, move most code to SGameEngine, SPlayState
 *   15Jun06 Move render Code to separate function, change init() calling
 *   12Jun06 TDK New Code
 */

#include <string>
#include <iostream>
#include "SDL.h"
#include "globals.h"
#include "Board.h"
#include "SGameEngine.h"
#include "SIntroState.h"

using std::string;

int main(int argc, char *argv[])
{   
    string rsrcdirectory = (string) *argv;
    rsrcdirectory = rsrcdirectory.substr( 0, rsrcdirectory.length() - 11 ) + "Resources/";
    
    SGameEngine game;
    
    // initialize the engine
    const SDL_version* version = SDL_Linked_Version();
    std::cout << "Snake World Tour 2006\nTyler Kieft\nLinked with SDL Version "
        << (int) version->major << "." << (int) version->minor << "." << (int) version->patch << std::endl;
    game.Init( "Snake World Tour 2006      v0.1 beta", rsrcdirectory );
    
    // load the game
    game.ChangeState( SIntroState::Instance() );
    
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