/*
 * FILNAMN:       Graphics.cc
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Nima Behnam 910103-0873 MED3
 *                Pernilla Petersson 910324-1288 MED3
 *                Klara Renström 910914-3306 MED3
 *                Johan Tidholm 911217-5675 MED3
 * DATUM:         2012-11-20
 *
 * BESKRIVNING: 
 * Här definieras funktionerna som är initerade i Graphics.h. Det är kod som sköter bildhanteringen.
 */

#include"Graphics.h"

//Laddar in bilder
SDL_Surface* Graphics::OnLoadBMP(const char* File)
{
  SDL_Surface* Surf_Temp = NULL;
  SDL_Surface* Surf_Return = NULL;

  if((Surf_Temp = SDL_LoadBMP(File)) == NULL)
    {
      return NULL;
    }

  Surf_Return = SDL_DisplayFormat(Surf_Temp);
  SDL_FreeSurface(Surf_Temp);

  return Surf_Return;
}

//Laddar in bilder
SDL_Surface* Graphics::OnLoad(const char* File)
{
  SDL_Surface* Surf_Temp = NULL;
  SDL_Surface* Surf_Return = NULL;

  if((Surf_Temp = IMG_Load(File)) == NULL)
    {
      return NULL;
    }

  Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
  SDL_FreeSurface(Surf_Temp);

  return Surf_Return;
}

//Ritar ut bilden på vald yta.
bool Graphics::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y)
{  
  if(Surf_Dest == NULL || Surf_Src == NULL)
    {
      return false;
    }

  SDL_Rect Destination;

  Destination.x = X;
  Destination.y = Y;

  SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &Destination);

  return true;
}

//Ritar ut en del av bilden på ett nytt ställe på ytan.
bool Graphics::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H)
{  
  if(Surf_Dest == NULL || Surf_Src == NULL)
    {
      return false;
    }

  SDL_Rect Destination;

  Destination.x = X;
  Destination.y = Y;

  SDL_Rect Source;

  Source.x = X2;
  Source.y = Y2;
  Source.w = W;
  Source.h = H;

  SDL_BlitSurface(Surf_Src, &Source, Surf_Dest, &Destination);

  return true;
}

//Gör en viss färg på bilden transparent.
bool Graphics::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B)
{
  if(Surf_Dest == 0)
    {
      return false;
    }

  SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));

  return true;
}
