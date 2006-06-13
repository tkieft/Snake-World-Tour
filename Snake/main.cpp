/* 
    Tyler Kieft
    June 12, 2006
    main.cpp - Initialize SDL
*/
   
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "SDL.h"
#include "load_image.h"
#include "globals.h"
#include "Board.h"

using std::cout;
using std::endl;
using std::string;

// Function prototypes
void init();
void deinit();

SDL_Surface* screen = NULL;
SDL_Surface* bg = NULL;
SDL_Event event;

int main(int argc, char *argv[])
{
    
    string rsrcdirectory = (string) *argv;
    rsrcdirectory = rsrcdirectory.substr( 0, rsrcdirectory.length() - 11 ) + "Resources/";
    //cout << rsrcdirectory;
    
    init();
    
    bg = load_image( rsrcdirectory + "snake.png" );
    //cout << bg->w << bg->h;
    SDL_Rect offset;
    offset.x = 0; offset.y = 0;

    SDL_BlitSurface( bg, NULL, screen, &offset );
    SDL_Flip( screen );
    
    Board myBoard( screen );
    myBoard.draw();
	
    int done = 0;
    while ( !done ) {

		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {

				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_KEYDOWN:
					/* Any keypress quits the app... */
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

void init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "Unable to initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    
    atexit( deinit );
    
    // Attempt to create a 640x480 window with 32 bit pixels
    screen = SDL_SetVideoMode( SCREENWIDTH, SCREENHEIGHT, SCREENBPP, SDL_SWSURFACE );
    
    if( screen == NULL )
    {
        cout << "Unable to set 640x480 video: " << SDL_GetError() << endl;
        exit(1);
    }
    
    // Set window title
    SDL_WM_SetCaption("Snake v0.1", NULL);
}

void deinit()
{
    SDL_FreeSurface( bg );
    /* Clean up the SDL Library */
    SDL_Quit();
    cout << "Quitting...";
}