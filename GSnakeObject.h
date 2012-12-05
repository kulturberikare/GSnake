/*
 * GSnakeObject.h
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */

#ifndef GSNAKEOBJECT_H_
#define GSNAKEOBJECT_H_

#include <SDL/SDL.h>
#include <deque> //
#include <vector>
#include "Define.h"
#include "GSnakeAnimation.h"
#include "GSurface.h"

enum {
	OBJECT_TYPE_GENERIC = 0,
	OBJECT_TYPE_PLAYER,
	OBJECT_TYPE_FOOD,
	OBJECT_TYPE_WALL
};

enum {
	OBJECT_FLAG_NONE = 0,
	OBJECT_FLAG_GHOST = 0x00000002,  //God mode-ish
	OBJECT_FLAG_MAPONLY = 0x00000004 //kolliderar bara med kartan
};

class GSnakeObject {
	public:
		GSnakeObject();
		bool CollisionCheck(int, int, int, int);
		void OnMove(float, float);
		void StopMove();

		virtual ~GSnakeObject();
		virtual bool OnLoad(char*, int, int);
		virtual void OnCleanup();
		virtual bool OnCollision(GSnakeObject*);
		virtual void OnLoop();
		virtual void OnRender(SDL_Surface*);

		static std::vector<GSnakeObject*> ObjectList;
		static std::deque<GSnakeObject*> TestSnake;
		bool Dead;
		bool MoveDown;
		bool MoveLeft;
		bool MoveRight;
		bool MoveUp;
		float X;
		float Y;
		int Width;
		int Height;
		int Type;
		int Flags;
		int Points;
		int AnimState;

	protected:
		GSnakeAnimation Anim_Control;
		SDL_Surface* Surf_Object;
		float SpeedX;
		float SpeedY;
};

class ObjectCollision {
	public:
		ObjectCollision();

		static std::vector<ObjectCollision> ObjectCollisionList;
		GSnakeObject* ObjectA;
		GSnakeObject* ObjectB;
};

#endif
