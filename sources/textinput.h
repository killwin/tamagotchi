#ifndef TEXT_INPUT

#define TEXT_INPUT 1

using namespace std;

#define W_LETTER 8
#define H_LETTER 16

#include <string>
#include <iostream>
#include "SDL.h"
#include <SDL/SDL_ttf.h>
#include "draw.h"

class TextInput
{
   private:
      unsigned max_letters;
      SDL_Rect rect_cursor, rect_text;
      SDL_Color color_backtext, color_text;
      TTF_Font *font;
      SDL_Surface *text_surface, *cursor, *erase_letter, *image;
      string str;
      void clear(void);

   public:
      TextInput(SDL_Color col0, SDL_Color col1, unsigned ml);
      ~TextInput();
      bool get(SDL_Event *ev, SDL_Surface *image, int x, int y);
      string &text(void);
};

#endif
