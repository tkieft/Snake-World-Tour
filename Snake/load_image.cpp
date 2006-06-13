/*
 *  load_image.cpp
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 */
#include <iostream>
#include "SDL_image.h"
#include "load_image.h"

SDL_Surface *load_image( string filename )
{
    //std::cout << "loading" << filename;
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    
    loadedImage = IMG_Load( filename.c_str() );
    
    if( loadedImage )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
    }
    else
        exit(1);
    
    //std::cout << optimizedImage;
    
    return optimizedImage;
}