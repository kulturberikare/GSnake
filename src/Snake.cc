/*
 * Snake.cc
 *
 *  Created on: 29 nov 2012
 *      Author: Nima
 */
#include "Snake.h"

Snake::Snake() {
}

bool Snake::OnLoad(const char* File, int Width, int Height) {
	if(GSnakeObject::OnLoad(File, Width, Height) == false) {
		return false;
	}

	return true;
}

void Snake::OnLoop() {
	GSnakeObject::OnLoop();
}

void Snake::OnRender(SDL_Surface* Surf_Display) {
	GSnakeObject::OnRender(Surf_Display);
}

void Snake::OnCleanup() {
	GSnakeObject::OnCleanup();
}
