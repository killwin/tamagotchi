#include "showBMP.h"

using namespace std;

ShowBMP::ShowBMP(const char *file)
{
    /* Charger une image BMP dans une surface*/
	try {
		image = IMG_Load(file);
		if (!image)
			throw string(string("Impossible de charger l'image") + file);
	}
	catch(string caught) {
		cerr << caught << endl;
	}
}

void ShowBMP::show(int x, int y, SDL_Surface *screen)
{

    SDL_Rect dest;

    /* Copie à l'écran.
	La surface ne doit pas être bloquée maintenant
     */
    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;
    SDL_BlitSurface(image, NULL, screen, &dest);

}
