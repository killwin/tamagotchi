#ifndef BMP

#define BMP 1

#include <string>
#include <iostream>
#include "SDL.h"
#include <SDL/SDL_image.h>

class ShowBMP
{
	public :
		ShowBMP(const char *file);
		void show(int x, int y, SDL_Surface *screen);
		
	private :
		SDL_Surface *image;
};

#endif
