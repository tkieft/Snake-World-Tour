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

using std::cout;
using std::endl;
using std::string;

// Function prototypes
SDL_Surface* init();
void render( SnakePlayer* theSnakes[], Board* theBoard );
void deinit();

SDL_Surface *bg = NULL;

int main(int argc, char *argv[])
{
    SDL_Event event;
    SnakePlayer* mySnakes[] = { NULL, NULL };
    mySnakes[0] = new SnakePlayer( 0xFFFFFF, "Tyler" );
    
    string rsrcdirectory = (string) *argv;
    rsrcdirectory = rsrcdirectory.substr( 0, rsrcdirectory.length() - 11 ) + "Resources/";
    //cout << rsrcdirectory;
    
    SDL_Surface* screen = init();
    Board* myBoard = new Board( screen, rsrcdirectory );
    
    bg = load_image( rsrcdirectory + "snake.png" );
    //cout << bg->w << bg->h;
    SDL_Rect offset;
    offset.x = 0; offset.y = 0;

    SDL_BlitSurface( bg, NULL, screen, &offset );
    SDL_Flip( screen );
	
    int done = 0;
    while ( !done ) {
        
        render( mySnakes, myBoard );

		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			switch( event.type ) {

				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_KEYUP:
					switch( event.key.keysym.sym )
                    {
                        case SDLK_LEFT: case SDLK_DOWN: case SDLK_UP: case SDLK_RIGHT:
                            mySnakes[0]->handleInput( &event );
                            break;
                        case SDLK_ESCAPE:
                            done = 1;
                            break;
                        default:
                            break;
                    }
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}
	}
	
	return(0);
}

void render( SnakePlayer* theSnakes[], Board* theBoard )
{
    theBoard->draw( theSnakes, 1 );
}

// init returns a pointer to SDL_Surface
SDL_Surface* init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "Unable to initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    
    atexit( deinit );
    
    // Attempt to create a 640x480 window with 32 bit pixels
    SDL_Surface* scr = SDL_SetVideoMode( SCREENWIDTH, SCREENHEIGHT, SCREENBPP, SDL_SWSURFACE );
    
    if( scr == NULL )
    {
        cout << "Unable to set 640x480 video: " << SDL_GetError() << endl;
        exit(1);
    }
    
    // Set window title
    SDL_WM_SetCaption("Snake v0.1", NULL);
    
    return scr;
}

void deinit()
{
    if( bg ) 
        SDL_FreeSurface( bg );
    
    /* Clean up the SDL Library */
    SDL_Quit();
    cout << "Quitting...";
}