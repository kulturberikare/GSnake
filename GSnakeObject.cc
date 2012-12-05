/*
 * GSnakeObject.cc
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */
#include "GSnakeObject.h"

std::vector<GSnakeObject*> GSnakeObject::ObjectList;
std::deque<GSnakeObject*> GSnakeObject::TestSnake;

std::vector<ObjectCollision> ObjectCollision::ObjectCollisionList;

ObjectCollision::ObjectCollision() {
	this->ObjectA = NULL;
	this->ObjectB = NULL;
}

GSnakeObject::GSnakeObject() {
	Surf_Object = NULL;

	X = 0;
	Y = 0;
	Width = 0;
	Height = 0;

	MoveDown = false;
	MoveLeft = false;
	MoveRight = false;
	MoveUp = false;

	Type = OBJECT_TYPE_GENERIC;

	Dead = false;
	Flags = OBJECT_FLAG_NONE;

	SpeedX = 0;
	SpeedY = 0;

	Points = 0;
	AnimState = 0;
}

GSnakeObject::~GSnakeObject() {
}

bool GSnakeObject::OnLoad(char* File, int Width, int Height) {
	if((Surf_Object = GSurface::OnLoad(File)) == NULL) {
		return false;
	}

	this->Width = Width;
	this->Height = Height;

	return true;
}

void GSnakeObject::OnRender(SDL_Surface* Surf_Display) {
	if(Surf_Object == NULL || Surf_Display == NULL) {
		return;
	}

    GSurface::OnDraw(Surf_Display, Surf_Object, X, Y, AnimState * Width, Anim_Control.GetCurrentFrame() * Height, Width, Height);
}

void GSnakeObject::OnCleanup() {
	if(Surf_Object) {
		SDL_FreeSurface(Surf_Object);
	}

	Surf_Object = NULL;
}

void GSnakeObject::OnMove(float MoveX, float MoveY) {
	X += MoveX;
	Y += MoveY;
}

void GSnakeObject::StopMove() {
	SpeedX = 0;
	SpeedY = 0;
	MoveDown = false;
	MoveLeft = false;
	MoveRight = false;
	MoveUp = false;
}

void GSnakeObject::OnLoop() {
	if(MoveLeft) {
		SpeedX = -0.5;
		SpeedY = 0;
	}
	else if(MoveRight) {
		SpeedX = 0.5;
		SpeedY = 0;
	}
	else if(MoveUp) {
		SpeedX = 0;
		SpeedY = -0.5;
	}
	else if(MoveDown) {
		SpeedX = 0;
		SpeedY = 0.5;
	}

	OnMove(SpeedX, SpeedY);
}

bool GSnakeObject::OnCollision(GSnakeObject* Object) {
	if(Object->Type == OBJECT_TYPE_FOOD) {
		Points += Object->Points;
		Object->X = rand() % (WWIDTH - Object->Width);
		Object->Y = rand() % (WHEIGHT - Object->Height);
	}
	else if (Object->Type == OBJECT_TYPE_WALL || Object->Type == OBJECT_TYPE_PLAYER) {
		Dead = true;
	}
	return true;
}

bool GSnakeObject::CollisionCheck(int ObjectX, int ObjectY, int ObjectW, int ObjectH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

	int tX = (int)X;
	int tY = (int)Y;

    left1 = tX;
    left2 = ObjectX;

    right1 = left1 + Width - 1;
    right2 = ObjectX + ObjectW - 1;

    top1 = tY;
    top2 = ObjectY;

    bottom1 = top1 + Height - 1;
    bottom2 = ObjectY + ObjectH - 1;


    if (bottom1 < top2) {
    	return false;
    }

    if (top1 > bottom2) {
    	return false;
    }

    if (right1 < left2) {
    	return false;
    }

    if (left1 > right2) {
    	return false;
    }

    return true;
}
