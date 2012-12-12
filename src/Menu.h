/*
 * FILNAMN:       Menu.h
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Klara Renström 9109143306 MED3
 *                Pernilla Petersson 9103241288 MED3
 *                Johan Tidholm 9112175675
 *    
 * DATUM:         2012-11-25
 *
 * BESKRIVNING: 
 * Här definieras Menu klassen som har hand om menyn. Den inkluderar Graphics.h för grafikhantering och 
 * Sound.h för ljudhantering. Dessa inkluderar sedan olika SDL bibliotek. Klassen ärver från CEvent 
 * där kod för eventhantering finns.
 *
 */

#ifndef _MENU_H_
#define _MENU_H_

#include <SDL/SDL_ttf.h>
#include "CEvent.h"
#include "Graphics.h"
#include "Sound.h"
#include "GSnake.h"

class Menu : public CEvent
{
 private:
  bool Running;
  bool Sounds;
  bool Instructions;
  bool Close; 
  bool Options;
  bool Difficulty;
  
  int State;
  int MinState;
  int MaxState;
  int StateClose;
  int BackMusic;

  //Ytor till menyn
  SDL_Surface* Surf_Display;
  SDL_Surface* Surf_Menu_Back;
  SDL_Surface* Surf_Frame;
  SDL_Surface* Surf_Sure;
  SDL_Surface* Surf_Sure_Frame;
  SDL_Surface* Surf_Opt_Back; 
  SDL_Surface* Surf_Helper; 
  SDL_Surface* Surf_Sound_Back;
  SDL_Surface* Surf_Diff_Back;

 public:
  Menu();
  int OnExecute();
  bool OnInit();
  void OnEvent(SDL_Event*);
  void OnExit();
  void OnKeyDown(SDLKey, SDLMod, Uint16);
  void OnRender();
  void OnCleanup();

};

#endif
