/*
 * GSnake.cc
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */
#include "GSnake.h"

GSnake::GSnake() {
	Surf_Display = NULL;
	Surf_Background = NULL;
	Running = true;
}

bool GSnake::OnInit() {
	if(SDL_INIT_EVERYTHING < 0) {
		return false;
	}

	if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		return false;
	}

	if((Surf_Background = GSurface::OnLoad("testbg2.png")) == false) {
		return false;
	}

	if(Snake.OnLoad("snakepiece.png", OBJSIDE, OBJSIDE) == false) {
		return false;
	}
	GSnakeObject::TestSnake.push_back(&Snake);

	if(Snake2.OnLoad("snakepiece.png", OBJSIDE, OBJSIDE) == false) {
		return false;
	}
	GSnakeObject::TestSnake.push_back(&Snake2);

	if(Snake3.OnLoad("snakepiece.png", OBJSIDE, OBJSIDE) == false) {
		return false;
	}
	GSnakeObject::TestSnake.push_back(&Snake3);

	if(Food.OnLoad("testobj.png", OBJSIDE, OBJSIDE) == false) {
		return false;
	}
	GSnakeObject::ObjectList.push_back(&Food);

	Snake.X = 150;
	Snake.Y = 150;
	Snake.MoveRight = true;
	Snake2.X = Snake.X - OBJSIDE;
	Snake2.Y = 150;
	Snake3.X = Snake2.X - OBJSIDE;
	Snake3.Y = 150;
	Snake.Type = OBJECT_TYPE_PLAYER;
	Food.Type = OBJECT_TYPE_FOOD;
	Food.X = 600;
	Food.Y = 200;
	Food.Points = 6;

	return true;
}

int GSnake::OnExecute() {
	if(OnInit() == false) {
		return -1;
	}

	SDL_Event Event;

	while(Running) {
		while(SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}

		OnLoop();
		OnRender();
	}

	OnCleanup();
	return 0;
}

void GSnake::OnCleanup() {
	for(unsigned int i = 0; i < GSnakeObject::TestSnake.size(); i++) {
		if(!GSnakeObject::TestSnake[i]) {
			continue;
		}

		GSnakeObject::TestSnake[i]->OnCleanup();
	}
	GSnakeObject::TestSnake.clear();

	for(unsigned int i = 0; i < GSnakeObject::ObjectList.size(); i++) {
		if(!GSnakeObject::ObjectList[i]) {
			continue;
		}

		GSnakeObject::ObjectList[i]->OnCleanup();
	}

	GSnakeObject::ObjectList.clear();
	SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(Surf_Background);
	SDL_Quit();
}

void GSnake::OnExit() {
	Running = false;
}

void GSnake::OnEvent(SDL_Event* Event) {
	GSnakeEvent::OnEvent(Event);
}

void GSnake::OnKeyDown(SDLKey sym, SDLMod, Uint16) {
	switch(sym) {
		case SDLK_UP: {
			if(!GSnakeObject::TestSnake[0]->MoveDown) {
				GSnakeObject::TestSnake[0]->MoveDown = false;
				GSnakeObject::TestSnake[0]->MoveLeft = false;
				GSnakeObject::TestSnake[0]->MoveRight = false;
				GSnakeObject::TestSnake[0]->MoveUp = true;
			}
			break;
			}
		case SDLK_DOWN: {
			if(!GSnakeObject::TestSnake[0]->MoveUp) {
				GSnakeObject::TestSnake[0]->MoveDown = true;
				GSnakeObject::TestSnake[0]->MoveLeft = false;
				GSnakeObject::TestSnake[0]->MoveRight = false;
				GSnakeObject::TestSnake[0]->MoveUp = false;
			}
			break;
		}
		case SDLK_LEFT: {
			if(!GSnakeObject::TestSnake[0]->MoveRight) {
				GSnakeObject::TestSnake[0]->MoveDown = false;
				GSnakeObject::TestSnake[0]->MoveLeft = true;
				GSnakeObject::TestSnake[0]->MoveRight = false;
				GSnakeObject::TestSnake[0]->MoveUp = false;
			}
			break;
		}

		case SDLK_RIGHT: {
			if(!GSnakeObject::TestSnake[0]->MoveLeft) {
				GSnakeObject::TestSnake[0]->MoveDown = false;
				GSnakeObject::TestSnake[0]->MoveLeft = false;
				GSnakeObject::TestSnake[0]->MoveRight = true;
				GSnakeObject::TestSnake[0]->MoveUp = false;
			}
			break;
		}
		case SDLK_s : {
			for(unsigned int i = 0; i < GSnakeObject::TestSnake.size(); i++) {
				GSnakeObject::TestSnake[i]->StopMove();
			}
			break;
		}

		default: {
			break; //goto
		}
	}
}

void GSnake::OnLoop() {
	SDL_WM_SetCaption("GSnake", "GSnake");
	for(unsigned int i = 1; i < GSnakeObject::TestSnake.size(); i++) {
		if(GSnakeObject::TestSnake[i]->X == GSnakeObject::TestSnake[i-1]->X) {
			if(GSnakeObject::TestSnake[0]->MoveUp) {
			GSnakeObject::TestSnake[i]->MoveDown = false;
			GSnakeObject::TestSnake[i]->MoveLeft = false;
			GSnakeObject::TestSnake[i]->MoveRight = false;
			GSnakeObject::TestSnake[i]->MoveUp = true;
			}
			else if(GSnakeObject::TestSnake[0]->MoveDown) {
				GSnakeObject::TestSnake[i]->MoveDown = true;
				GSnakeObject::TestSnake[i]->MoveLeft = false;
				GSnakeObject::TestSnake[i]->MoveRight = false;
				GSnakeObject::TestSnake[i]->MoveUp = false;
			}
		}

		if(GSnakeObject::TestSnake[i]->Y == GSnakeObject::TestSnake[i-1]->Y) {
			if(GSnakeObject::TestSnake[0]->MoveLeft) {
				GSnakeObject::TestSnake[i]->MoveDown = false;
				GSnakeObject::TestSnake[i]->MoveLeft = true;
				GSnakeObject::TestSnake[i]->MoveRight = false;
				GSnakeObject::TestSnake[i]->MoveUp = false;
			}
			else if(GSnakeObject::TestSnake[0]->MoveRight) {
				GSnakeObject::TestSnake[i]->MoveDown = false;
				GSnakeObject::TestSnake[i]->MoveLeft = false;
				GSnakeObject::TestSnake[i]->MoveRight = true;
				GSnakeObject::TestSnake[i]->MoveUp = false;
			}
		}
	}

	if(Snake.CollisionCheck(Food.X, Food.Y, Food.Width, Food.Height)) {
		Snake.Points += Food.Points;
		Food.X = rand() % (WWIDTH - Food.Width);
		Food.Y = rand() % (WHEIGHT - Food.Height);
	}

	for(unsigned int i = 0;i < GSnakeObject::TestSnake.size();i++) {
		if(!GSnakeObject::TestSnake[i]) {
			continue;
		}
		GSnakeObject::TestSnake[i]->OnLoop();
	}

	for(unsigned int i = 0;i < GSnakeObject::ObjectList.size();i++) {
		if(!GSnakeObject::ObjectList[i]) {
			continue;
		}

		GSnakeObject::ObjectList[i]->OnLoop();
	}

//	for(unsigned int i = 0;i < ObjectCollision::ObjectCollisionList.size();i++) {
//		GSnakeObject* ObjectA = ObjectCollision::ObjectCollisionList[i].ObjectA;
//		GSnakeObject* ObjectB = ObjectCollision::ObjectCollisionList[i].ObjectB;
//		if(ObjectA == NULL || ObjectB == NULL) {
//			continue;
//		}
//	}
//
//	ObjectCollision::ObjectCollisionList.clear();
}

void GSnake::OnRender() {
	GSurface::OnDraw(Surf_Display, Surf_Background, 0, 0);
	for(unsigned int i = 0; i < GSnakeObject::TestSnake.size(); i++) {
		if(!GSnakeObject::TestSnake[i]) continue;

		GSnakeObject::TestSnake[i]->OnRender(Surf_Display);
	}

	for(unsigned int i = 0; i < GSnakeObject::ObjectList.size(); i++) {
		if(!GSnakeObject::ObjectList[i]) continue;

		GSnakeObject::ObjectList[i]->OnRender(Surf_Display);
	}

	SDL_Flip(Surf_Display);
}

/* ==================================================================================== */

int main(int argc, char* argv[]) {
	GSnake Game;
	return Game.OnExecute();
}
