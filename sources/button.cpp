#include "button.h"

Button::Button(string title, SDL_Surface *img, int x, int y) : image(img), on_off(false), press(false)
{
	
   button.x = x;
   button.y = y;
   button.w = size_text * W_LETTER + 2 * W_CORNER;
   button.h = H_CORNER;	
   size_text = title.length();
		
   TTF_Font *font;
   font = NULL;

   SDL_Color color_text = {0, 0, 0};    
   rect_text.x = x + W_CORNER;
   rect_text.y = y + 16;

   try {
      font = TTF_OpenFont("/usr/share/fonts/truetype/unifont/unifont.ttf", 16);
      if(!font)
         throw string("Can't load fonts");
		
      img_button_left_off = IMG_Load("imgs/button_left.png");
      if(!img_button_left_off)
         throw string("Can't load button_left.png");
			
      img_button_right_off = IMG_Load("imgs/button_right.png");
      if(!img_button_right_off)
         throw string("Can't load button_right.png");
	
      img_button_center_off = IMG_Load("imgs/button_center.png");
      if(!img_button_center_off)
         throw string("Can't load button_center.png");

      img_button_left_on = IMG_Load("imgs/button_left.png");
      if(!img_button_left_on)
         throw string("Can't load button_left.png");
			
      img_button_right_on = IMG_Load("imgs/button_right.png");
      if(!img_button_right_on)
         throw string("Can't load button_right.png");
	
      img_button_center_on = IMG_Load("imgs/button_center.png");
      if(!img_button_center_on)
         throw string("Can't load button_center.png");

      text_surface = TTF_RenderText_Solid(font, title.c_str(), color_text);
      if (!text_surface)
         throw string("Can't create the surface text_surface");

   }
   catch(string caught) {
		
     if(font) {
        TTF_CloseFont(font);
     }
		
     if(img_button_left_off)
        SDL_FreeSurface(img_button_left_off);

     if(img_button_right_off)
        SDL_FreeSurface(img_button_right_off);

     if(img_button_center_off)
        SDL_FreeSurface(img_button_center_off);

     if(img_button_left_on)
        SDL_FreeSurface(img_button_left_on);

     if(img_button_right_on)
        SDL_FreeSurface(img_button_right_on);

     if(img_button_center_on)
        SDL_FreeSurface(img_button_center_on);

     if(text_surface)
        SDL_FreeSurface(text_surface);

      cerr << caught << endl;
      throw;
   }

   // on images are off images without red color
   SDL_LockSurface(img_button_left_on);
   SDL_LockSurface(img_button_right_on);
   SDL_LockSurface(img_button_center_on);

   img_button_left_on->format->Rmask = 0;
   img_button_right_on->format->Rmask = 0;
   img_button_center_on->format->Rmask = 0;

   SDL_UnlockSurface(img_button_left_on);
   SDL_UnlockSurface(img_button_right_on);
   SDL_UnlockSurface(img_button_center_on);
	
}

void Button::show(void) {
   show(img_button_left_off, img_button_center_off, img_button_right_off);
}

void Button::show(SDL_Surface *img_left, SDL_Surface *img_center, SDL_Surface *img_right) {
	
   SDL_Rect dest;
   dest.x = button.x;
   dest.y = button.y;
   dest.w = W_CORNER;
   dest.h = H_CORNER;

   // blit left button image
   SDL_BlitSurface(img_left, NULL, image, &dest);
   
   // blit center button with the good lenght 	
   for(unsigned i = 0; i < size_text; ++i) {
      dest.x += dest.w;
      SDL_BlitSurface(img_center, NULL, image, &dest);
      dest.w = W_LETTER;
   }

   dest.x += dest.w;
   dest.w = W_CORNER;
   
   // blit right image button
   SDL_BlitSurface(img_right, NULL, image, &dest);

   // blit the text on button		
   SDL_BlitSurface(text_surface, NULL, image, &rect_text);
}

bool Button::eval(SDL_Event ev) {
		
	bool tmp_on_off = on_off;

	if(ev.motion.x > button.x && ev.motion.x < button.x + button.w
	&& ev.motion.y > button.y && ev.motion.y < button.y + button.h)
		on_off = true;
	else
		on_off = false;
		
	if(on_off != tmp_on_off)

		if(on_off)
			show(img_button_left_on, img_button_center_on, img_button_right_on);
		else
			show(img_button_left_off, img_button_center_off, img_button_right_off);

	if(on_off && ev.type == SDL_MOUSEBUTTONDOWN)
		return true;
	else
		return false;
}
