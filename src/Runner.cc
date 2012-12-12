/*
 * FILNAMN:       Runner.cc
 * LABORATION:    Projekt - Snake
 * PROGRAMMERARE: Pernilla Petersson 910324-1288 MED3
 *                Klara Renstr�m 910914-3306 MED3
 * DATUM:         2012-12-08
 *
 * BESKRIVNING 
 * Denna kod initerar ett GSnake-objekt och k�r sedan spelet. Det finns olika 
 * states som s�tts till true och false beroende p� om spelet eller menyn ska 
 * k�ras.
 */

#include "Menu.h"

int main()
{
  GSnake init;
  init.Volume = 128;
  GSnake::Diff = 1;

  while(GSnake::running)
    {
      if(GSnake::menu)
	{
	  Menu head_menu;
	  head_menu.OnExecute();
	}
      if(GSnake::play)
	{	 
	  GSnake GSnake;
	  GSnake.OnExecute();
	}
    } 
  return 0;
}
