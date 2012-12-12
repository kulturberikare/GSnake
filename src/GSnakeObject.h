/*
 * GSnakeObject.h
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */

#ifndef GSNAKEOBJECT_H_
#define GSNAKEOBJECT_H_

#include <SDL/SDL.h>
#include <deque>
#include <vector>
#include "Define.h"
#include "Graphics.h"

enum Direction {
	NONE = 0,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class GSnakeObject {
	public:
		GSnakeObject();
		virtual ~GSnakeObject() = default;
		bool CollisionCheck(int, int, int, int);

		void OnMove(float, float);
		void StopMove();

		virtual GSnakeObject* clone();
		virtual bool OnLoad(const char*, int, int);
		virtual void OnCleanup();
		virtual void OnLoop();
		virtual void OnRender(SDL_Surface*);

		friend class GSnake;

	protected:
		static std::vector<GSnakeObject*> ObjectList;
		static std::deque<GSnakeObject*> Snake;
		SDL_Surface* Surf_Object;
		float SpeedX;
		float SpeedY;
		int Direction;
		int Width;
		int Height;
		int Points;
		int X;
		int Y;
};

#endif
