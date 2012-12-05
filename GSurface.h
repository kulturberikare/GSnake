/*
 * GSurface.h
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */

#ifndef GSURFACE_H_
#define GSURFACE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class GSurface {
	public:
		GSurface();
		static SDL_Surface* OnLoad(char*);
		static bool OnDraw(SDL_Surface*, SDL_Surface*, int, int);
		static bool OnDraw(SDL_Surface*, SDL_Surface*, int, int, int, int, int, int);
		static bool Transparent(SDL_Surface*, int, int, int);
};

#endif
