/*
 * FILNAMN:       CEvent.cc
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Pernilla Petersson 910324-1288 MED3
 *                Klara Renström 910914-3306 MED3
 * DATUM:         2012-12-06
 *
 * BESKRIVNING 
 * I denna klass definieras funktionerna initierade i CEvent.h. 
 * Det är funktioner som tar han om event som inträffar t.ex. när tangentbordet används.
 */


#include "CEvent.h"
 
CEvent::CEvent() {}
 
CEvent::~CEvent() {}
 
//Kontrollerar vilket event som uppstått.
void CEvent::OnEvent(SDL_Event* Event) 
{
  switch(Event->type) 
    {
  
    case SDL_KEYDOWN:
      {
	OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
	break;
      }
    
    case SDL_QUIT:
      {
	OnExit();
	break;
      }
 
    case SDL_SYSWMEVENT:
      {
	break;
      }

    default:
      {
	OnUser(Event->user.type,Event->user.code, Event->user.data1, Event->user.data2);
	break;
      }
    }
}

void CEvent::OnKeyDown(SDLKey, SDLMod, Uint16) {}

void CEvent::OnExit() {}

void CEvent::OnUser(Uint8, int, void*, void*) {}
