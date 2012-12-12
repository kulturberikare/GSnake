/*
 * GSnake.cc
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */
#include "GSnake.h"

GSnake::GSnake() {
	Surf_Display = nullptr;
	Surf_Background = nullptr;
	Dead = false;	
	Running = true;
	Difficulty = 0;
	Game_Over = nullptr;
	Points = nullptr;
	Return = nullptr;
	score_font = nullptr;
	GO_font = nullptr;	
	points_string = "Score: 0";
	color = {255, 255, 255, 255};

	Surf_Paus = NULL;
	Surf_Paus_Frame = NULL;
	Paus = true;
	MaxX = 2;
	MinX = 0;
	PausState = 0;
	Paus = false;
	GameMusic = 0;

	menu = true;
	play = false;
	running = true;
}

bool GSnake::menu;
bool GSnake::play;
bool GSnake::running;
int GSnake::Volume;
int GSnake::SavedVolume;
int GSnake::Diff;

bool GSnake::OnInit() {
	if(SDL_INIT_EVERYTHING < 0) {
		return false;
	}

	if(TTF_Init() < 0)
	  {
	    return false;
	  }

	if((score_font = TTF_OpenFont("./src/FreeMono.ttf", 26)) == nullptr)
	  {
	    return false;
	  }

	if((GO_font = TTF_OpenFont("./src/FreeMono.ttf", 50)) == nullptr)
	  {
	    return false;
	  }

	if((Game_Over = TTF_RenderText_Solid(GO_font, "GAME OVER", color)) == nullptr)
	  {
	    return false;
	  }

	if((Points = TTF_RenderText_Solid(score_font, points_string.c_str(), color)) == nullptr)
	  {
	    return false;
	  }

	if((Return = TTF_RenderText_Solid(score_font, "Press return to continue", color)) == nullptr)
	  {
	    return false;
	  }

	if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		return false;
	}

	if((Surf_Background = Graphics::OnLoad("./gfx/background.jpg")) == false) {
		return false;
	}

	if((Surf_Paus = Graphics::OnLoadBMP("./gfx/pause_menu.bmp")) == false) {
		return false;
	}
	if((Surf_Paus_Frame = Graphics::OnLoadBMP("./gfx/Pause_frame.bmp")) == false) {
		return false;
	}

	if(SnakePart.OnLoad("./gfx/snakepiece.png", OBJSIDE, OBJSIDE) == false) {
		return false;
	}
	GSnakeObject::Snake.push_back(&SnakePart);

	if(Food.OnLoad("./gfx/food.png", OBJSIDE, OBJSIDE) == false) {
		return false;
	}
	GSnakeObject::ObjectList.push_back(&Food);

	if(LeftWall.OnLoad("./gfx/wall.png", OBJSIDE, WHEIGHT) == false) {
		return false;
	}
	GSnakeObject::ObjectList.push_back(&LeftWall);

	if(LowerWall.OnLoad("./gfx/wallrot.png", WWIDTH, OBJSIDE) == false) {
		return false;
	}
	GSnakeObject::ObjectList.push_back(&LowerWall);

	if(RightWall.OnLoad("./gfx/wall.png", OBJSIDE, WHEIGHT) == false) {
		return false;
	}
	GSnakeObject::ObjectList.push_back(&RightWall);

	if(UpperWall.OnLoad("./gfx/wallrot.png", WWIDTH, OBJSIDE) == false) {
		return false;
	}
	GSnakeObject::ObjectList.push_back(&UpperWall);

	//Gör Surf_Paus_Frame transparent
	Graphics::Transparent(Surf_Paus_Frame, 0, 0, 0);

	SnakePart.X = 100;
	SnakePart.Y = 150;
	GSnakeObject::Snake.push_front(GSnakeObject::Snake[0]->clone());
	GSnakeObject::Snake.push_front(GSnakeObject::Snake[0]->clone());
	GSnakeObject::Snake.push_front(GSnakeObject::Snake[0]->clone());
	GSnakeObject::Snake.push_front(GSnakeObject::Snake[0]->clone());

	if(Diff == 1)
	  {
	    Difficulty = EASY;
	  }
	if(Diff == 2)
	  {
	    Difficulty = MEDIUM;
	  }
	if(Diff == 3)
	  {
	    Difficulty = HARD;
	  }

	Food.Direction = NONE;
	Food.X = 600;
	Food.Y = 200;
	Food.Points = 3 * Difficulty;
	LeftWall.Direction = NONE;
	LowerWall.X = OBJSIDE;
	LowerWall.Y = WHEIGHT - OBJSIDE;
	LowerWall.Direction = NONE;
	RightWall.X = WWIDTH - OBJSIDE;
	RightWall.Direction = NONE;
	UpperWall.X = OBJSIDE;
	UpperWall.Direction = NONE;

	//Ljudhantering
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	  {
	    return false;
	  }

	if((GameMusic = Sound::SoundControl.OnLoad("./music/POL-purple-hills-short.wav")) == -1)
	  {
	    return false;
	  }

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

		//Sätter bolym till aktuellt värde och spelar musik
		Mix_Volume(-1, GSnake::Volume);
		Sound::SoundControl.Play(GameMusic);
	}

	OnCleanup();
	return 0;
}

void GSnake::OnCleanup() {
	GSnakeObject::Snake.back()->OnCleanup();

	for(unsigned int i = 0; i < GSnakeObject::Snake.size()-1; i++) {
		if(!GSnakeObject::Snake[i]) {
			continue;
		}
		delete GSnakeObject::Snake[i];
	}
	GSnakeObject::Snake.clear();

	for(unsigned int i = 0; i < GSnakeObject::ObjectList.size(); i++) {
		if(!GSnakeObject::ObjectList[i]) {
			continue;
		}

		GSnakeObject::ObjectList[i]->OnCleanup();
	}

	GSnakeObject::ObjectList.clear();
	SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(Surf_Background);
	SDL_FreeSurface(Game_Over);
	SDL_FreeSurface(Points);
	SDL_FreeSurface(Return);
	SDL_FreeSurface(Surf_Paus);
	SDL_FreeSurface(Surf_Paus_Frame);
	TTF_CloseFont(score_font);
	TTF_CloseFont(GO_font);
	Sound::SoundControl.OnCleanup();
	Mix_CloseAudio();
	TTF_Quit();	
	SDL_Quit();
}

void GSnake::OnExit() {
  play = false;
  menu = true;
	Running = false;
}

void GSnake::OnEvent(SDL_Event* Event) {
	CEvent::OnEvent(Event);
}

void GSnake::OnKeyDown(SDLKey sym, SDLMod, Uint16) {
	if(GSnakeObject::Snake[0]->Direction == GSnakeObject::Snake[1]->Direction)

		switch(sym) {
			case SDLK_UP: {
			  if(!Paus)
			    {
				if(GSnakeObject::Snake[0]->Direction != DOWN) {
					GSnakeObject::Snake[0]->Direction = UP;
				}
				break;
			    }
			  break;
			}
			case SDLK_DOWN: {
			  if(!Paus)
			    {
				if(GSnakeObject::Snake[0]->Direction != UP) {
					GSnakeObject::Snake[0]->Direction = DOWN;
				}
				break;
			    }
			  break;
			}
			case SDLK_LEFT: {
			  if(!Paus)
			    {
				if(GSnakeObject::Snake[0]->Direction != RIGHT) {
					GSnakeObject::Snake[0]->Direction = LEFT;
				}
				break;
			    }
			  if(Paus)
			    {
			      if(!(PausState == MinX))
				{
				  PausState -= 1;
				}
			      break;
			    }
			  break;
			}

			case SDLK_RIGHT: {
			  if(!Paus)
			    {
				if(GSnakeObject::Snake[0]->Direction != LEFT) {
					GSnakeObject::Snake[0]->Direction = RIGHT;
				}
				break;
			    }
			  if(Paus)
			    {
			      if(!(PausState == MaxX))
			    {
			      PausState += 1;
			    }
			    break;
			}
			  break;
			}
			case SDLK_p : {
			  if(GSnakeObject::Snake[0]->Direction != NONE) {
			    for(unsigned int i = 0; i < GSnakeObject::Snake.size(); i++) {
			      saved_motions.push_back(GSnakeObject::Snake[i]->Direction);
			      GSnakeObject::Snake[i]->StopMove();
			    }
			  }
			  Paus = true;
			  break;
			}

 case SDLK_RETURN : {
   if(Paus)
     {
       if(PausState == 0)
	 {
	   Paus = false;
	   for(unsigned int i = 0; i < saved_motions.size(); i++) {
	     GSnakeObject::Snake[i]->Direction = saved_motions[i];
	   }
	   saved_motions.clear();			  
			  
	   break;
	 }
       if(PausState == 1) //Sound off
	 {
	   if(GSnake::Volume == 0)
	     {
	       GSnake::Volume = GSnake::SavedVolume;
	       Mix_Volume(-1, GSnake::Volume);
	     }
	   else
	     {
	       GSnake::SavedVolume = GSnake::Volume;
	       GSnake::Volume = 0;
	       Mix_Volume(-1, GSnake::Volume);
	     }
	 }
       if(PausState == 2)
	 {
	   OnExit();
	   break;
	 }
     }

   if(Dead)
     {
       play = false;
       menu = true;
       OnExit();
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

	for (int i = GSnakeObject::Snake.size() - 1; i > 0 ; --i)
	{
		if(GSnakeObject::Snake[i-1]->Direction == UP && GSnakeObject::Snake[i]->Direction != UP && GSnakeObject::Snake[i]->Y - GSnakeObject::Snake[i-1]->Y == OBJSIDE)
		{
			GSnakeObject::Snake[i]->Direction = UP;
		}

		if(GSnakeObject::Snake[i-1]->Direction == DOWN && GSnakeObject::Snake[i]->Direction != DOWN && GSnakeObject::Snake[i-1]->Y - GSnakeObject::Snake[i]->Y == OBJSIDE)
		{
			GSnakeObject::Snake[i]->Direction = DOWN;
		}

		if(GSnakeObject::Snake[i-1]->Direction == RIGHT && GSnakeObject::Snake[i]->Direction != RIGHT && GSnakeObject::Snake[i-1]->X - GSnakeObject::Snake[i]->X == OBJSIDE)
		{
			GSnakeObject::Snake[i]->Direction = RIGHT;
		}

		if(GSnakeObject::Snake[i-1]->Direction == LEFT && GSnakeObject::Snake[i]->Direction != LEFT && GSnakeObject::Snake[i]->X - GSnakeObject::Snake[i-1]->X == OBJSIDE)
		{
			GSnakeObject::Snake[i]->Direction = LEFT;
		}

	}

	// SNAKE-FOOD COLLISION DETECTOR
	if(GSnakeObject::Snake[0]->CollisionCheck(Food.X, Food.Y, Food.Width, Food.Height)) {
		SnakePart.Points += Food.Points;
		srand ( time(NULL) );
		Food.X = OBJSIDE + rand() % (WWIDTH - 3 * OBJSIDE);
		Food.Y = OBJSIDE + rand() % (WHEIGHT - 3 * OBJSIDE);
		GSnakeObject::Snake.push_front(GSnakeObject::Snake[0]->clone());
		points_string = "Score: " + convertInt(SnakePart.Points);
		Points = TTF_RenderText_Solid(score_font, points_string.c_str(), color);
	}

	// SNAKE-WALL COLLISION DETECTORS
	if(GSnakeObject::Snake[0]->CollisionCheck(LeftWall.X, LeftWall.Y, LeftWall.Width, LeftWall.Height)) {
		for(unsigned int i = 0; i < GSnakeObject::Snake.size(); i++) {
			GSnakeObject::Snake[i]->StopMove();
			Dead = true;
		}	
	}

	if(GSnakeObject::Snake[0]->CollisionCheck(LowerWall.X, LowerWall.Y, LowerWall.Width, LowerWall.Height)) {
		for(unsigned int i = 0; i < GSnakeObject::Snake.size(); i++) {
			GSnakeObject::Snake[i]->StopMove();
			Dead = true;
		}
	}

	if(GSnakeObject::Snake[0]->CollisionCheck(RightWall.X, RightWall.Y, RightWall.Width, RightWall.Height)) {
		for(unsigned int i = 0; i < GSnakeObject::Snake.size(); i++) {
			GSnakeObject::Snake[i]->StopMove();
			Dead = true;
		}
	}

	if(GSnakeObject::Snake[0]->CollisionCheck(UpperWall.X, UpperWall.Y, UpperWall.Width, UpperWall.Height)) {
		for(unsigned int i = 0; i < GSnakeObject::Snake.size(); i++) {
			GSnakeObject::Snake[i]->StopMove();
			Dead = true;
		}
	}

	// SNAKE-SNAKE COLLISION DETECTOR
	for(unsigned int i = 1; i < GSnakeObject::Snake.size(); i++) {
		if(GSnakeObject::Snake[0]->CollisionCheck(GSnakeObject::Snake[i]->X, GSnakeObject::Snake[i]->Y, GSnakeObject::Snake[i]->Width, GSnakeObject::Snake[i]->Height)) {
			for(unsigned int i = 0; i < GSnakeObject::Snake.size(); i++) {
				GSnakeObject::Snake[i]->StopMove();
				Dead = true;
			}
		}
	}

	// FOOD-SNAKE COLLISION DETECTOR (Matens nya plats hamnar på ormen)
	for(unsigned int i = 1; i < GSnakeObject::Snake.size(); i++) {
		if(Food.CollisionCheck(GSnakeObject::Snake[i]->X, GSnakeObject::Snake[i]->Y, GSnakeObject::Snake[i]->Width, GSnakeObject::Snake[i]->Height)) {
			srand ( time(NULL) );
			Food.X = OBJSIDE + rand() % (WWIDTH - 3 * OBJSIDE);
			Food.Y = OBJSIDE + rand() % (WHEIGHT - 3 * OBJSIDE);
		}
	}

	// OBJECT LOOPING
	for(unsigned int i = 0;i < GSnakeObject::Snake.size();i++) {
		if(!GSnakeObject::Snake[i]) {
			continue;
		}
		GSnakeObject::Snake[i]->OnLoop();
	}

	for(unsigned int i = 0;i < GSnakeObject::ObjectList.size();i++) {
		if(!GSnakeObject::ObjectList[i]) {
			continue;
		}

		GSnakeObject::ObjectList[i]->OnLoop();
	}

	// SLOW LOOP SPEED
	int SlowFactor = 160 / Difficulty;
	SDL_Delay(SlowFactor);

}

void GSnake::OnRender() {
	Graphics::OnDraw(Surf_Display, Surf_Background, 0, 0);
	for(unsigned int i = 0; i < GSnakeObject::Snake.size(); i++) {
		if(!GSnakeObject::Snake[i]) continue;

		GSnakeObject::Snake[i]->OnRender(Surf_Display);
	}

	for(unsigned int i = 0; i < GSnakeObject::ObjectList.size(); i++) {
		if(!GSnakeObject::ObjectList[i]) continue;

		GSnakeObject::ObjectList[i]->OnRender(Surf_Display);
	}

	Graphics::OnDraw(Surf_Display, Points, 600 , 10);
	if(Dead) {
	  Graphics::OnDraw(Surf_Display, Game_Over, 275 , 250);
	  Graphics::OnDraw(Surf_Display, Return, 235 , 300);
	}

	if(Paus)
	  {
	    Graphics::OnDraw(Surf_Display, Surf_Paus, 200, 150);
	    Graphics::OnDraw(Surf_Display, Surf_Paus_Frame, (200+ PausState*140), 330);
	  }

	SDL_Flip(Surf_Display);
}

std::string GSnake::convertInt(int num) {
  std::stringstream ss;
  ss << num;
  return ss.str();
}
