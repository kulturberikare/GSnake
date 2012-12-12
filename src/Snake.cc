/*
 * FILNAMN:       Snake.cc
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Nima Behnam 910103-0873 MED3
 * DATUM:         2012-11-29
 *
 * BESKRIVNING 
 * Detta är klassen för själva ormen
 *
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
