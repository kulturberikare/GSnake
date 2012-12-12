/*
 * Snake.h
 *
 *  Created on: 29 nov 2012
 *      Author: Nima
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include "GSnakeObject.h"

class Snake : public GSnakeObject {
	public:
		Snake();
		bool OnLoad(const char*, int, int);
		void OnCleanup();
		void OnLoop();
		void OnRender(SDL_Surface*);
};

#endif

