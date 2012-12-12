/*
 * FILNAMN:       Sound.cc
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Klara Renstr�m 9109143306 MED3
 *                                    
 * DATUM:         2012-12-04
 *
 * BESKRIVNING: 
 * H�r definieras funktioner som initierades i Sound.h. Det �r den klass som
 * tar hand om ljudhanteringen i programmet.
 * 
 */

#include "Sound.h"

Sound Sound::SoundControl;

Sound::Sound()
{}

//Ladda in ljudobjekt
int Sound::OnLoad(const char* File)
{ 
  Mix_Chunk* TempSound = NULL;

  if((TempSound = Mix_LoadWAV(File)) == NULL)
    {
      return -1;
    }

  SoundList.push_back(TempSound);

  return (SoundList.size() - 1);
}

//St�dar
void Sound::OnCleanup()
{
  for(unsigned int i = 0; i < SoundList.size(); i++)
    {
      Mix_FreeChunk(SoundList[i]);
    }

  SoundList.clear();
}

//Spelar ljudet.
void Sound::Play(unsigned int ID)
{
  if(ID >= SoundList.size())
    {
      return;
    }
  if (SoundList[ID] == NULL) 
    {
      return;
    }
  Mix_PlayChannel(-1, SoundList[ID], 0);
}

