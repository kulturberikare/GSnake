/*
 * FILNAMN:       Menu.cc
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Klara Renström 9109143306 MED3
 *                Pernilla Petersson 9103241288 MED3
 *                Johan Tidholm 9112175675
 *    
 * DATUM:         2012-11-25
 *
 * BESKRIVNING: 
 * I denna klass definieras de funktioner som initeras i Menu.h. Klassen sköter uppritandet av huvudmenyn, ljudet till den och 
 * samma för dess olika undermenyer.
 * I filen inkluderas Menu.h som i sin tur inkluderat SDL och SDL_Mixer för grafik och ljudhantering.
 *
 */

#include "Menu.h"
#include "GSnake.h"
#include <iostream>

using namespace std;

Menu::Menu() //konstruktor som initerar alla ytor och andra värden initialt.
{
  Running = true;
  Sounds = false;
  Instructions = false;
  Close = false;
  Options = false;
  Difficulty = false;

  State = 0;
  MinState = 0;
  MaxState = 2;
  StateClose = 0;
  BackMusic = 0;

  Surf_Display = NULL;
  Surf_Menu_Back = NULL;
  Surf_Frame = NULL;

  Surf_Sure = NULL;
  Surf_Sure_Frame = NULL;

  Surf_Opt_Back = NULL;
  Surf_Helper = NULL;
  Surf_Sound_Back = NULL;
  Surf_Diff_Back = NULL;
}


//Kör programmet
int Menu::OnExecute()
{
  if(OnInit() == false)
    {
      return -1;
    }

  SDL_Event Event;

  while(Running)
    {
      while(SDL_PollEvent(&Event))
	{
	  OnEvent(&Event);
	}
      OnRender();

      Mix_Volume(-1, GSnake::Volume);
      Sound::SoundControl.Play(BackMusic); //Spelar bakgrundsljud
    }
 
    OnCleanup();

  return 0;
}

//Läser in alla filer och olika SDL bibiliotek. Returnerar false om något misslyckats.
bool Menu::OnInit()
{
  //  Grafik
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
      return false;
    }
 
  if((Surf_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) 
    {
      return false;
    }

  //Till första menyn
  if((Surf_Menu_Back = Graphics::OnLoadBMP("./gfx/Menu.bmp")) == NULL)
    {
      return false;
    }

  if((Surf_Frame = Graphics::OnLoadBMP("./gfx/Frame.bmp")) == NULL)
    {
      return false;
    }

  if((Surf_Sure = Graphics::OnLoadBMP("./gfx/Sure.bmp")) == NULL)
    {
      return false;
    }
  if((Surf_Sure_Frame = Graphics::OnLoadBMP("./gfx/sure_frame.bmp")) == NULL)
    {
      return false;
    }
  //Till Optionsmenyn
  if((Surf_Opt_Back = Graphics::OnLoadBMP("./gfx/Opt.bmp")) == NULL)
    {
      return false;
    }

  if((Surf_Helper = Graphics::OnLoadBMP("./gfx/Instructions.bmp")) == NULL)
    {
      return false;
    }

  //Till Soundmenyn
  if((Surf_Sound_Back = Graphics::OnLoadBMP("./gfx/Sounds.bmp")) == NULL)
    {
      return false;
    }

  //Till Svårighetsgradsmenyn
  if((Surf_Diff_Back = Graphics::OnLoadBMP("./gfx/Difficulty.bmp")) == NULL)
    {
      return false;
    }

  //Gör bakgrunden i Frame och Sure_Frame transparent
  Graphics::Transparent(Surf_Frame, 0, 0, 0);
  Graphics::Transparent(Surf_Sure_Frame, 0, 0, 0);

  //Ljud
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
      return false;
    }

  if((BackMusic = Sound::SoundControl.OnLoad("./music/POL-lost-hero-short.wav")) == -1)
    {
      return false;
    }

  //Döper runtan till Menu
  SDL_WM_SetCaption( "Menu", NULL);

  return true;
}

//Tar hand om event som inträffar
void Menu::OnEvent(SDL_Event* Event)
{
  GSnakeEvent::OnEvent(Event);
}

//Avslutar menyn
void Menu::OnExit()
{
  Running = false;
  GSnake::running = false;
}

//Gör olika saker när man trycker på tangentbordet.
void Menu::OnKeyDown(SDLKey sym, SDLMod, Uint16)
{ 
  if(Sounds || Options || Difficulty) //Bestämmer hur många steg markören kan flyttas
    {
      MaxState = 3;
      MinState = 0;
    }
  else
    {
      MaxState = 2;
      MinState = 0;
    }

  switch(sym)
    {
    case SDLK_UP: //Pil upp
      if(State - 1 < MinState)
	{
	  break;
	}
      else
	{
	  State -= 1;
	}

      break;

    case SDLK_DOWN: //Pil ner
      if(State + 1 > MaxState)
	{
	  break;
	}
      else
	{
	  State += 1;
	}
      break;

    case SDLK_RIGHT: //Pil höger
      {
	if(Close)
	  {
	    if(StateClose == 0)
	      {
		StateClose += 1;
	      }
	    break;
	  }
      }
      break;

    case SDLK_LEFT: //Pil vänster
      {
	if(Close)
	  {
	    if(StateClose == 1)
	      {
		StateClose -= 1;
	      }
	    break;
	  }
      }
      break;

    case SDLK_RETURN: //Return
      {
	if(Sounds) //Undersöker vilken meny som är aktuell och utför åtgärder
	  {
	    if(State == 0) //Stänger volymen
	      {
		GSnake::SavedVolume = GSnake::Volume;
		GSnake::Volume = 0;
		Mix_Volume(-1, GSnake::Volume);
	      }
	    if(State == 1) //Sänker volymen
	      {
		GSnake::Volume = GSnake::Volume - 10;
		Mix_Volume(-1, GSnake::Volume); 
	      }
	    if(State == 2) //Höjer volymen
	      {
		GSnake::Volume = GSnake::Volume + 10;
		Mix_Volume(-1, GSnake::Volume);
	      }
	    if(State == 3)
	      {
		Sounds = false;
		Options = true;
		State = 0;
	      }
	    break;
	  }
     
	if(Options)
	  {
	    if(State == 0)
	      {
		Instructions = true;
	      }
	    if(State == 1)
	      {
		Sounds = true;
		Options = false;
		State = 0;
	      }
	    if(State == 2)
	      {
		Difficulty = true;
		Options = false;
		State = 0;
	      }
	    if(State == 3)
	      {
		Options = false;
		State = 0;
	      }
	    break;
	  }

	if(Close)
	  {
	    if(StateClose == 0)
	      {
		OnExit();
	      }
	    else 
	      {
		Close = false;
		StateClose = 0;
	      }
	    break;
	  }

	if(Difficulty)
	  {
	    if(State == 0) //Nivå Easy
	      {
		GSnake::Diff = 1;
	      }
	    if(State == 1) //Nivå Medium
	      {
		GSnake::Diff = 2;
	      }
	    if(State == 2) //Nivå Hard
	      {
		GSnake::Diff = 3;
	      }
	    if(State == 3)
	      {
		Difficulty = false;
		Options = true;
		State = 0;
	      }
	    break;
	  }

	if(!Options && !Sounds && !Difficulty)
	  {
	    if(State == 0)
	      {
		GSnake::menu = false;
		GSnake::play = true;
		Running = false;
	      }
	    if(State == 1)
	      {
		Options = true;
		State = 0;	  
	      }
	    if(State == 2)
	      {
		Close = true;
	      }
	    break;
	  }
      }
      break;
    case SDLK_BACKSPACE:
      {
	if(Instructions)     
	  {
	    Instructions = false;
	    break;
	  }
      }
      break;

    default: {}

    }
}

//Målar bilderna
void Menu::OnRender()
{
  if(Options)
    {
      Graphics::OnDraw(Surf_Display, Surf_Opt_Back, 0, 0);
      Graphics::OnDraw(Surf_Display, Surf_Frame, 195, (140 + State*90));
    }

  if(Instructions)
    {
      Graphics::OnDraw(Surf_Display, Surf_Opt_Back, 0, 0);
      Graphics::OnDraw(Surf_Display, Surf_Helper, 120, 140);
    }
  if(Sounds)
    {
      Graphics::OnDraw(Surf_Display, Surf_Sound_Back, 0, 0);
      Graphics::OnDraw(Surf_Display, Surf_Frame, 195, (140 + State*90));
    }
  if(Difficulty)
    {
      Graphics::OnDraw(Surf_Display, Surf_Diff_Back, 0, 0);
      Graphics::OnDraw(Surf_Display, Surf_Frame, 195, (140 + State*90));
    }

  if(!Options && !Sounds && !Difficulty)
    {
      Graphics::OnDraw(Surf_Display, Surf_Menu_Back, 0, 0);
      Graphics::OnDraw(Surf_Display, Surf_Frame, 195, (140 + State*90));
    }
  if(Close)
    {
      Graphics::OnDraw(Surf_Display, Surf_Menu_Back, 0, 0);
      Graphics::OnDraw(Surf_Display, Surf_Sure, 120, 160);
      Graphics::OnDraw(Surf_Display, Surf_Sure_Frame, (168 + StateClose*235), 295);
    }
  SDL_Flip(Surf_Display);
}

//Städar
void Menu::OnCleanup()
{
  SDL_FreeSurface(Surf_Display);
  SDL_FreeSurface(Surf_Menu_Back);  
  SDL_FreeSurface(Surf_Frame);
  SDL_FreeSurface(Surf_Sure_Frame);
  SDL_FreeSurface(Surf_Sure);
  SDL_FreeSurface(Surf_Opt_Back);
  SDL_FreeSurface(Surf_Helper);
  SDL_FreeSurface(Surf_Sound_Back);
  SDL_FreeSurface(Surf_Diff_Back);
  Sound::SoundControl.OnCleanup(); 
  Mix_CloseAudio();

  SDL_Quit();
}
