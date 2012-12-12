//
//
#include "CText.h"

CText::Ctext()
{
  was_init = 0;
}

bool CText::OnInit()
{
  if(TTF_Init() < 0)
    {
      return false;
    }

  if(was_init == 0)
    {
      return false;
    }

  TTF_OpenFont("test.ttf", 28);

  return true;
}

void CText::OnCleanup()
{
  TTF_Quit();
}

int CText::OnLoad(char* File)
{
}
