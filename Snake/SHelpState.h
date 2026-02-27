/*
 *	SHelpState.h
 *	Snake
 *
 *	Created by Tyler on 6/13/07
 *  Copyright 2007 Tyler Kieft. All rights reserved.
 *
 *	CHANGELOG:
 *  13Jun07 TDK New Code.
 *
 */

#ifndef SHELPSTATE_H
#define SHELPSTATE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SGameEngine.h"
#include "SGameState.h"


class SHelpState: public SGameState {
public:
	void Init( SGameEngine* game );
	void Cleanup();
	
	void Pause();
    void Resume();
    
    void HandleEvents( SGameEngine* game );
    void Update( SGameEngine* game );
    void Draw( SGameEngine* game );
    
    static SHelpState* Instance() { return &snakeHelpState; }

protected:
	SHelpState() {}
	~SHelpState() {}
	
private:
	static SHelpState snakeHelpState;
	
	SDL_Surface* bg;
	SDL_Surface* fontSurface;
	
	SDL_Color bgColor;
	SDL_Color titleColor1, titleColor2, titleColor3;
	SDL_Color textColor;
	
	TTF_Font* titleFont;
	TTF_Font* textFont;
};

#endif
