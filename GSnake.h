/*
 * GSnake.h
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */

#ifndef GSNAKE_H_
#define GSNAKE_H_

#include <SDL/SDL.h>
#include "Define.h"
#include "GSnakeEvent.h"
#include "GSnakeObject.h"
#include "GSurface.h"

class GSnake : public GSnakeEvent {
	public:
		GSnake();
		bool OnInit();
		int OnExecute();
		void OnCleanup();
		void OnExit();
		void OnEvent(SDL_Event*);
		void OnKeyDown(SDLKey, SDLMod, Uint16);
		void OnLoop();
		void OnRender();

	private:
		bool Running;
		GSnakeObject Snake;
		GSnakeObject Snake2; //
		GSnakeObject Snake3; //
		GSnakeObject Food;
		SDL_Surface* Surf_Display;
		SDL_Surface* Surf_Background;
};

#endif
