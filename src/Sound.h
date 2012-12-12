/*
 * FILNAMN:       Sound.h
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Klara Renström 9109143306 MED3
 *                    
 * DATUM:         2012-12-04
 *
 * BESKRIVNING: 
 * Denna klass initierar ljudhantering. SDL-bilioteket SDL_mixer inkluderas. 
 *
 */

#ifndef _SOUND_H_
#define _SOUND_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vector>

class Sound
{
 public:
  static Sound SoundControl;
  std::vector<Mix_Chunk*> SoundList;

  Sound();

  int OnLoad(const char* File);
  void OnCleanup();
  void Play(unsigned int);

};

#endif
