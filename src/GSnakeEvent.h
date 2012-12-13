/*
 * FILNAMN:       GSnakeEvent.h
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Nima Behnam 910103-0873 MED3
 *                Pernilla Petersson 910324-1288 MED3
 *                Klara Renström 910914-3306 MED3
 *                Johan Tidholm 911217-5675 MED3
 * DATUM:         2012-12-06
 *
 * BESKRIVNING 
 * I denna klass definieras de olika event som uppstår dvs. tangentbordshantering och avslutning.
 *
 */




#ifndef _CEVENT_H_
    #define _CEVENT_H_
 
#include <SDL/SDL.h>
 
class GSnakeEvent {
    public:
        GSnakeEvent();
        virtual ~GSnakeEvent();

        virtual void OnEvent(SDL_Event*);
        virtual void OnKeyDown(SDLKey, SDLMod, Uint16);
        virtual void OnExit();
        virtual void OnUser(Uint8, int, void* , void*);
};
 
#endif
