/*
 * FILNAMN:       Graphics.h
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Pernilla Petersson 910324-1288 MED3
 *                Klara Renström 910914-3306 MED3
 * DATUM:         2012-11-20
 *
 * BESKRIVNING: 
 * Detta är klassen som definierar det grafiska. Den inkluderar SDL biblioteket
 * som hanterar grafik.
 */


#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Graphics
{
 public:
  static SDL_Surface* OnLoad(const char*);
  static SDL_Surface* OnLoadBMP(const char*);

  static bool OnDraw(SDL_Surface*, SDL_Surface*, int ,int);
  static bool OnDraw(SDL_Surface*, SDL_Surface*, int, int, int, int, int, int);
  static bool Transparent(SDL_Surface*, int, int, int);
};

#endif
