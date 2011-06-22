#ifndef CONNEXION

#define CONNEXION 1

#define X_INPUT 298
#define Y_INPUT 144
#define LINES_SPACE 66

#include <string>
#include <iostream>
#include <fstream>
#include "SDL.h"

#include "timeleft.h"
#include "showBMP.h"
#include "textinput.h"
#include "button.h"
#include "sql.h"

using namespace std;

class Connexion
{
   public :
	
   Connexion(SDL_Surface *image);
   bool connected(void);
   bool duplecated_login(void);

   private :
      bool connex_is_ok, same_name;
      //FILE * File;
      string link, login, passwd, name_tama;
      SDL_Surface *text_surface;
};

#endif
