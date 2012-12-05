/*
 * GSnakeEvent.h
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */

#ifndef GSNAKEEVENT_H_
#define GSNAKEEVENT_H_

#include <SDL/SDL.h>

class GSnakeEvent {
    public:
        GSnakeEvent();
        virtual ~GSnakeEvent();
        virtual void OnEvent(SDL_Event*);
        virtual void OnExit();
        virtual void OnExpose();
        virtual void OnInputBlur();
        virtual void OnInputFocus();
        virtual void OnKeyDown(SDLKey, SDLMod, Uint16);
        virtual void OnKeyUp(SDLKey, SDLMod, Uint16);
        virtual void OnMouseBlur();
        virtual void OnMouseFocus();
        virtual void OnMouseMove(int, int, int, int, bool,bool,bool);
        virtual void OnMouseWheel(bool, bool);    //Not implemented
        virtual void OnLButtonDown(int, int);
        virtual void OnLButtonUp(int, int);
        virtual void OnMButtonDown(int, int);
        virtual void OnMButtonUp(int, int);
        virtual void OnRButtonDown(int, int);
        virtual void OnRButtonUp(int, int);
        virtual void OnMinimize();
        virtual void OnRestore();
        virtual void OnResize(int,int);
        virtual void OnUser(Uint8, int, void*, void*);
};

#endif
