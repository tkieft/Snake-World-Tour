/*
 *  load_image.h
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 */

#ifndef LOAD_IMAGE_H
#define LOAD_IMAGE_H

#include <string>
#include "SDL.h"
using std::string;

SDL_Surface* load_image( string filename, int r = 0, int g = 0, int b = 0 );

#endif