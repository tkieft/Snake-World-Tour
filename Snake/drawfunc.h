/*
 *  drawfunc.h
 *  Snake
 *
 *  Created by Tyler on 6/12/06.
 *  Copyright 2006 Tyler Kieft. All rights reserved.
 *
 *  CHANGELOG:
 *  19Jun06 TDK Drawnum shall get its own class.
 *  18Jun06 TDK Add drawnum.
 *  12Jun06 TDK New Code.
 */

#ifndef DRAWFUNC_H
#define DRAWFUNC_H

#include "SDL.h"

void drawrect( int x, int y, int width, int height, Uint32 col, SDL_Surface* gScreen );
char* scoreToChar( int score );

#endif