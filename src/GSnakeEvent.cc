/*
 * GSnakeEvent.cc
 *
 *  Created on: 26 nov 2012
 *      Author: nimbe760
 */
#include "GSnakeEvent.h"

void GSnakeEvent::OnExpose() {
    //Pure virtual, do nothing
}

void GSnakeEvent::OnExit() {
    //Pure virtual, do nothing
}

GSnakeEvent::GSnakeEvent() {
}

GSnakeEvent::~GSnakeEvent() {
    //Do nothing
}

void GSnakeEvent::OnEvent(SDL_Event* Event) {
    switch(Event->type) {
        case SDL_ACTIVEEVENT: {
            switch(Event->active.state) {
                case SDL_APPMOUSEFOCUS: {
                    if ( Event->active.gain )    OnMouseFocus();
                    else                OnMouseBlur();

                    break;
                }
                case SDL_APPINPUTFOCUS: {
                    if ( Event->active.gain )    OnInputFocus();
                    else                OnInputBlur();

                    break;
                }
                case SDL_APPACTIVE:    {
                    if ( Event->active.gain )    OnRestore();
                    else                OnMinimize();

                    break;
                }
            }
            break;
        }

        case SDL_KEYDOWN: {
            OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }

        case SDL_KEYUP: {
            OnKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
            break;
        }

        case SDL_MOUSEMOTION: {
            OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_MOUSEBUTTONUP:    {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }

        case SDL_QUIT: {
            OnExit();
            break;
        }

        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }

        case SDL_VIDEORESIZE: {
            OnResize(Event->resize.w,Event->resize.h);
            break;
        }

        case SDL_VIDEOEXPOSE: {
            OnExpose();
            break;
        }

        default: {
            OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
            break;
        }
    }
}

void GSnakeEvent::OnInputFocus() {
    //Pure virtual
}

void GSnakeEvent::OnInputBlur() {
    //Pure virtual
}

void GSnakeEvent::OnKeyDown(SDLKey, SDLMod, Uint16) {
    //Pure virtual
}

void GSnakeEvent::OnKeyUp(SDLKey, SDLMod, Uint16) {
    //Pure virtual
}

void GSnakeEvent::OnMouseFocus() {
    //Pure virtual
}

void GSnakeEvent::OnMouseBlur() {
    //Pure virtual
}

void GSnakeEvent::OnMouseMove(int, int, int, int, bool, bool, bool) {
    //Pure virtual
}

void GSnakeEvent::OnMouseWheel(bool, bool) {
    //Pure virtual
}

void GSnakeEvent::OnLButtonDown(int, int) {
    //Pure virtual
}

void GSnakeEvent::OnLButtonUp(int, int) {
    //Pure virtual
}

void GSnakeEvent::OnRButtonDown(int, int) {
    //Pure virtual
}

void GSnakeEvent::OnRButtonUp(int, int) {
    //Pure virtual
}

void GSnakeEvent::OnMButtonDown(int, int) {
    //Pure virtual
}

void GSnakeEvent::OnMButtonUp(int, int) {
    //Pure virtual
}

void GSnakeEvent::OnMinimize() {
    //Pure virtual
}

void GSnakeEvent::OnRestore() {
    //Pure virtual
}

void GSnakeEvent::OnResize(int, int) {
    //Pure virtual
}


void GSnakeEvent::OnUser(Uint8, int, void*, void*) {
    //Pure virtual
}
