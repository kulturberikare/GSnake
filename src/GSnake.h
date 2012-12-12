/*
 * FILNAMN:       CSnake.h
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Nima Behnam 910103-0873 MED3
 *                Pernilla Petersson 910324-1288 MED3
 *                Klara Renström 910914-3306 MED3
 *                Johan Tidholm 911217-5675 MED3
 * DATUM:         2012-11-26
 *
 * BESKRIVNING 
 * Detta är själva spelklassen, alla funktioner som spelet kräver för att fungera finns deklarerade här. 
 */

#ifndef GSNAKE_H_
#define GSNAKE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include "Define.h"
#include "GSnakeObject.h"
#include "Snake.h"
#include "Sound.h"
#include "Graphics.h"
#include "CEvent.h"

enum Difficulties {
	EASY = 1,
	MEDIUM = 2,
	HARD = 4
};

class GSnake : public CEvent {
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

		int GameMusic;
		int MinX;
		int MaxX;
		int PausState;
		bool Paus;

		static bool menu;
		static bool play;
		static bool running;
		static int Volume;
		static int SavedVolume;
		static int Diff;


	private:
		bool Dead;
		bool Running;
		Snake SnakePart;
		int Difficulty;
		GSnakeObject Food;
		GSnakeObject LeftWall;
		GSnakeObject LowerWall;
		GSnakeObject RightWall;
		GSnakeObject UpperWall;
		SDL_Surface* Surf_Display;
		SDL_Surface* Surf_Background;
		SDL_Surface* Game_Over;
		SDL_Surface* Points;
		SDL_Surface* Return;
		SDL_Surface* Surf_Paus;
		SDL_Surface* Surf_Paus_Frame;
		TTF_Font* score_font;
		TTF_Font* GO_font;
		SDL_Color color;
		std::string points_string;
		std::string convertInt(int);
		std::vector<int> saved_motions;
};

#endif
