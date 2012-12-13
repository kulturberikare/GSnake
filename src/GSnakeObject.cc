/*
 * GSnakeObject.cc
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */
#include "GSnakeObject.h"

// Initiering av beh�llare f�r olika objekt
std::vector<GSnakeObject*> GSnakeObject::ObjectList;
std::deque<GSnakeObject*> GSnakeObject::Snake;

// Objektkonstruktor
GSnakeObject::GSnakeObject() {
	Surf_Object = NULL;

	X = 0;
	Y = 0;
	Width = 0;
	Height = 0;

	Direction = RIGHT;

	SpeedX = 0;
	SpeedY = 0;

	Points = 0;
}

// Laddar in en fil till ett objekt
bool GSnakeObject::OnLoad(const char* File, int Width, int Height) {
	if((Surf_Object = Graphics::OnLoad(File)) == NULL) {
		return false;
	}

	this->Width = Width;
	this->Height = Height;

	return true;
}

// Ritar ett objekt
void GSnakeObject::OnRender(SDL_Surface* Surf_Display) {
	if(Surf_Object == NULL || Surf_Display == NULL) {
		return;
	}

	Graphics::OnDraw(Surf_Display, Surf_Object, X, Y);
}

// St�dar upp ett objekt
void GSnakeObject::OnCleanup() {
	if(Surf_Object) {
		SDL_FreeSurface(Surf_Object);
	}
	Surf_Object = NULL;
}

// Kopierar ett objekt, dock avsedd f�r ormdelar s� villkor finns. Inte riktigt en kopieringskonstruktor.
GSnakeObject* GSnakeObject::clone() {
	GSnakeObject* Obj = new GSnakeObject;

	Obj->Surf_Object = Surf_Object;

	if(Snake[0]->Direction == DOWN) {
		Obj->X = X;
		Obj->Y = Y + OBJSIDE;
	}
	else if(Snake[0]->Direction == LEFT) {
		Obj->X = X - OBJSIDE;
		Obj->Y = Y;
	}
	else if(Snake[0]->Direction == RIGHT) {
		Obj->X = X + OBJSIDE;
		Obj->Y = Y;
	}
	else if(Snake[0]->Direction == UP) {
		Obj->X = X;
		Obj->Y = Y - OBJSIDE;
	}

	Obj->Width = Width;
	Obj->Height = Height;

	if(Snake[0]->Direction == DOWN) {
		Obj->Direction = DOWN;
	}
	else if(Snake[0]->Direction == LEFT) {
		Obj->Direction = LEFT;
	}
	else if(Snake[0]->Direction == RIGHT) {
		Obj->Direction = RIGHT;
	}
	else if(Snake[0]->Direction == UP) {
		Obj->Direction = UP;
	}

	Obj->SpeedX = Snake[0]->SpeedX;
	Obj->SpeedY = Snake[0]->SpeedY;

	Obj->Points = Points;

	return Obj;
}

// R�relsefunktion
void GSnakeObject::OnMove(float MoveX, float MoveY) {
	X += MoveX;
	Y += MoveY;
}

// Stannar r�relse
void GSnakeObject::StopMove() {
	SpeedX = 0;
	SpeedY = 0;
	Direction = NONE;
}

// Objektloop
void GSnakeObject::OnLoop() {
	if(Direction == LEFT) {
		SpeedX = -OBJSIDE;
		SpeedY = 0;
	}
	else if(Direction == RIGHT) {
		SpeedX = OBJSIDE;
		SpeedY = 0;
	}
	else if(Direction == UP) {
		SpeedX = 0;
		SpeedY = -OBJSIDE;
	}
	else if(Direction == DOWN) {
		SpeedX = 0;
		SpeedY = OBJSIDE;
	}

	OnMove(SpeedX, SpeedY);
}

// Collision detector
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
