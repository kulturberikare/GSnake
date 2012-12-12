/*
 * FILNAMN:       Snake.h
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Nima Behnam 910103-0873 MED3
 * DATUM:         2012-11-29
 *
 * BESKRIVNING 
 * Funktionsdeklarationer och klassdeklaration för ormen.
 * 
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

