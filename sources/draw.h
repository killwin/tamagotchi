#ifndef DRAW

#define DRAW 1

#include <iostream>
#include "SDL.h"

class CDraw
{ 

   public :

      CDraw(SDL_Surface *img);
      void full_color(SDL_Color color); 
      SDL_Surface *image;
};

#endif
