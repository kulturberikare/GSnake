/*
 * FILNAMN:       CEvent.h
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Pernilla Petersson 910324-1288 MED3
 *                Klara Renstr�m 910914-3306 MED3
 * DATUM:         2012-12-06
 *
 * BESKRIVNING 
 * I denna klass definieras de olika event som uppst�r dvs. tangentbordshantering och avslutning.
 *
 */




#ifndef _CEVENT_H_
    #define _CEVENT_H_
 
#include <SDL/SDL.h>
 
class CEvent {
    public:
        CEvent();
        virtual ~CEvent();

        virtual void OnEvent(SDL_Event*);
        virtual void OnKeyDown(SDLKey, SDLMod, Uint16);
        virtual void OnExit();
        virtual void OnUser(Uint8, int, void* , void*);
};
 
#endif
