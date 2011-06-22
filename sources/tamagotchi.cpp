#include <iostream>
#include "SDL.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "timeleft.h"
#include "connexion.h"
#include "showBMP.h"

using namespace std;

int main(int argc, char *argv[])
{
   if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
      cerr << "Can't init SDL: " << SDL_GetError() << endl;
      return 1;
   }

   atexit(SDL_Quit);

   SDL_Surface *screen;
   screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
   if (!screen) {
      cerr << "Can't set video mode: " << SDL_GetError() << endl;
      return 1;
   }

   if(TTF_Init()==-1) {
      cerr << "Can't init TTF: " << SDL_GetError() << endl;
      return 1;
   }

   SDL_Event event;
   TTF_Font *font;
   font = NULL;

   try {   
      font = TTF_OpenFont("/usr/share/fonts/truetype/unifont/unifont.ttf", 16);
      if(!font)
         throw string("Can't load fonts");
   }
   catch(string &caught) {
	   
	   TTF_Quit();
	   SDL_FreeSurface(screen);
	   
	   cerr << caught << endl;
	   return 1;
   }

   ShowBMP showbmp("imgs/backg.png");
   Connexion *connexion = NULL;

   // connect to database
   do {
      showbmp.show(0, 0, screen);
      try {
         connexion = new Connexion(screen);
      }
      catch(string &caught) {

         TTF_Quit();
         TTF_CloseFont(font);
         SDL_FreeSurface(screen);

         cerr << caught << endl;
         return 1;
      }
      
      if(connexion->duplecated_login()) {
		  showbmp.show(0, 0, screen);
		  
		  SDL_Color color_text = {0, 0, 0};
		  SDL_Rect dest_text;
		  dest_text.x = 100;
		  dest_text.y = 100;
		  SDL_Surface *text_surface;
		  Button *button_ok;
		  
		  try {
			  
             button_ok = new Button("OK", screen, 150, 140);
		     text_surface = TTF_RenderText_Solid(font, "This login is already registrated !", color_text);
             if (!text_surface)
                throw string("Can't create the surface text-surface");
		  }
		  catch(string &caught) {
			  TTF_Quit();
			  TTF_CloseFont(font);
              SDL_FreeSurface(screen);

              cerr << caught << endl;
              return 1;
 		  }
 		  
          SDL_BlitSurface(text_surface, NULL, screen, &dest_text);
          button_ok->show();
 		  
 		  bool next = false;
 		  
  		  while(!next) {
			  SDL_Delay(TimeLeft());
			  while(SDL_PollEvent(&event)) {
				  SDL_UpdateRect(screen, 0, 0, 0, 0);
				  switch (event.type) {
					  case SDL_MOUSEMOTION:
					  case SDL_MOUSEBUTTONDOWN:
					     if(button_ok->eval(event))
							next = true;
                      break;
                      case SDL_QUIT:
	                     TTF_Quit();
	                     SDL_FreeSurface(screen);
                         return 0;
				  }
			  }
		  }
	  }
         
   
   } while(!connexion->connected());

   showbmp.show(0, 0, screen);

   bool quit_game = false;
	
   while(!quit_game) {
		
      SDL_Delay(TimeLeft());

      while(SDL_PollEvent(&event)) {
         SDL_UpdateRect(screen, 0, 0, 0, 0);

         switch (event.type) {
            case SDL_MOUSEMOTION:
            break;

            case SDL_MOUSEBUTTONDOWN:
            break;

            case SDL_QUIT:
	          TTF_Quit();
	          SDL_FreeSurface(screen);
              return 0;
         }
      }
   }
   return 0;
}
