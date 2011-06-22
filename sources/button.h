#ifndef BUTTON

#define BUTTON 1

#define W_CORNER 32
#define H_CORNER 64

#include <string>
#include <iostream>
#include "SDL.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "textinput.h"

using namespace std;

class Button {
    public :
    
    Button(std::string title, SDL_Surface *img, int x, int y);
    bool eval(SDL_Event ev);
    void show(void);
    
    private :
    
    void show(SDL_Surface *img_left, SDL_Surface *img_center, SDL_Surface *img_right);
    
    bool on_off, press;
    int size_text;
    SDL_Rect button, rect_text;
    SDL_Surface *image;
    SDL_Surface *img_button_left_off, *img_button_right_off, *img_button_center_off;
	SDL_Surface *img_button_left_on, *img_button_right_on, *img_button_center_on;
	SDL_Surface *text_surface;

};

#endif
