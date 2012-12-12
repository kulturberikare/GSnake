#ifndef _CTEXT_H_
#define _CTEXT_H_


#include <SDL/SDL_ttf>

class CText
{
 private:
  int was_init;

 public:

  CText();
  bool OnInit();
  void OnCleanup();
  int OnLoad(char* File);

};

#endif
