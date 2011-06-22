#include "draw.h"

CDraw::CDraw(SDL_Surface *img) : image(img) {
}

void CDraw::full_color(SDL_Color col) {
	
   SDL_LockSurface(image);
   for(unsigned i = 0; i < image->h * image->w; ++i)
      *((unsigned *)image->pixels + i) = (col.r << 16) + (col.g << 8) + col.b;
   SDL_UnlockSurface(image);
}
