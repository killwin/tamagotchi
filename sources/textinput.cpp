#include "textinput.h"

TextInput::TextInput(SDL_Color col0, SDL_Color col1, unsigned ml) : color_backtext(col0), color_text(col1), max_letters(ml)
{
   SDL_EnableUNICODE(SDL_ENABLE);

   try {
      font = TTF_OpenFont("/usr/share/fonts/truetype/unifont/unifont.ttf", 16);
      if(!font)
         throw string("Can't load fonts");
		
      cursor = SDL_CreateRGBSurface(SDL_HWSURFACE, W_LETTER, H_LETTER, 32, 0, 0, 0, 0);
      
      if(!cursor)
         throw string("Can't create image corsor");
      
      CDraw *draw_cursor = new CDraw(cursor);
      draw_cursor->full_color(color_text);

      erase_letter = SDL_CreateRGBSurface(SDL_HWSURFACE, W_LETTER, H_LETTER, 32, 0, 0, 0, 0);

      if(!erase_letter)
         throw string("Can't create image erase_letter");
      
      CDraw *draw_erase_letter = new CDraw(erase_letter);
      draw_erase_letter->full_color(color_backtext);

   }
   catch(string caught) {

      if(font) {
         TTF_CloseFont(font);
      }

      if(cursor)
         SDL_FreeSurface(cursor);

      if(erase_letter)
         SDL_FreeSurface(erase_letter);

      cerr << caught << endl;
      throw;
	}
}

TextInput::~TextInput()
{
   SDL_EnableUNICODE(SDL_DISABLE);
}

bool TextInput::get(SDL_Event *ev, SDL_Surface *img, int x, int y)
{

   rect_text.x = rect_cursor.x = x;
   rect_text.y = rect_cursor.y = y;
	
   image = img;
			
   if(ev) {
      if(ev->type == SDL_KEYDOWN) {		

         if(ev->key.keysym.sym == SDLK_RETURN) {
            rect_cursor.x += W_LETTER * str.length();
            SDL_BlitSurface(erase_letter, NULL, image, &rect_cursor);
            return false;
         }

         if(str.length() > max_letters && ev->type != SDLK_RETURN)
            return true;

         char caracter = ev->key.keysym.unicode;	
		
         // only for letters and numbers	
         if((caracter > 64 && caracter < 91) || (caracter > 96 && caracter < 123)|| (caracter > 47 && caracter < 58))
            str += caracter;

         if((ev->key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ))
            str.erase((str.length() - 1));
		
         try {
            text_surface = TTF_RenderText_Solid(font, str.c_str(), color_text);
			if (!text_surface)
				throw string("Can't create image text_surface");
         }
         catch(string caught) {
            cerr << caught << endl;
            throw;
         }

         rect_cursor.x += W_LETTER * (str.length() - 1);
         SDL_BlitSurface(erase_letter, NULL, image, &rect_cursor);
         SDL_BlitSurface(text_surface, NULL, image, &rect_text);
         rect_cursor.x += W_LETTER;
         SDL_BlitSurface(cursor, NULL, image, &rect_cursor);
         rect_cursor.x += W_LETTER;
         SDL_BlitSurface(erase_letter, NULL, image, &rect_cursor);
      }
   }
   else {
      clear();
      SDL_BlitSurface(cursor, NULL, image, &rect_cursor);
   }

   return true;
}

void TextInput::clear(void) {

   rect_cursor.x = rect_text.x;

   for(int i = 0; i < max_letters + 1; ++i) {
      rect_cursor.x += W_LETTER;
      SDL_BlitSurface(erase_letter, NULL, image, &rect_cursor);
   }
		
   str.clear();
   rect_cursor.x = rect_text.x;
}

string &TextInput::text(void) {
	return str;
}
