#include "connexion.h"

Connexion::Connexion(SDL_Surface *image) : connex_is_ok(false), same_name(false), text_surface(NULL)
{

   TTF_Font *font;
   SDL_Color color_text = {0, 0, 0};
   SDL_Rect dest_text;
   dest_text.x = 150;
   dest_text.y = 320;
   font = NULL;
   fstream file;
   file.open("connexion.tam", ios::in | ios::out);
	
   try {

      if(!file)
         throw string("Can't open file connexion.tam");

      font = TTF_OpenFont("/usr/share/fonts/truetype/unifont/unifont.ttf", 16);
      if(!font)
         throw string("Can't load fonts");
			
      text_surface = TTF_RenderText_Solid(font, "Do you want to continue registration ?", color_text);
      if (!text_surface)
         throw string("Can't create the surface text-surface");

   }
   catch(string &caught) {
      if (file)
         file.close();

      if(font) {
         TTF_CloseFont(font);
         TTF_Quit();
      }

      if(text_surface)
         SDL_FreeSurface(text_surface);

      cerr << caught << endl;
      throw;
   }
	
   file >> link;
   cout << "link : " << link.c_str() << endl;

   if(file.good()) {

      Sql *sql;
      cout << "First connexion" << endl;
      try {
         sql = new Sql("tamagotchi", link, "client001", "#?XxWw03");
      }
      catch (const string &caught) {
         cerr << caught << endl;
         throw;
      }
      
      Button *button_yes;
      Button *button_no;
      try {
         button_yes = new Button("yes", image, 200, 340);
         button_no = new Button("No", image, 300, 340);
	  }
	  catch(string caught) {
	     cerr << caught << endl;
         throw;
      }
		
      ShowBMP showbmp = ShowBMP("imgs/connexion.png");
      showbmp.show(50, 50, image);
      SDL_Color color_text = {255, 255, 255};
      SDL_Color color_backtext = {0, 0, 0};
      TextInput *textinput;
      
      try {
         textinput = new TextInput(color_backtext, color_text, 26);
      }
	  catch(string caught) {
	     cerr << caught << endl;
         throw;
      }

      SDL_Event event;
      int y_input = Y_INPUT;
      int id_input = 0;
      bool completed = false;
      string input_txt[3]; // for login, passwd and tamagotchi name
      bool conn_exit = false;

      // for login
      textinput->get(NULL, image, X_INPUT, y_input);

      while(!conn_exit) {
		
         SDL_Delay(TimeLeft());

         while(SDL_PollEvent(&event)) {
				
            SDL_UpdateRect(image, 0, 0, 0, 0);

            switch (event.type) {
					
               case SDL_MOUSEBUTTONDOWN:
               case SDL_MOUSEMOTION:
					
                  if(completed) {
                     if(button_yes->eval(event)) {
                        vector<string> req(3);
                        req[0] = login;
                        req[1] = passwd;
                        req[2] = name_tama;
                        // insert values in database
                        try {
                           if(!sql->insert_new(req)) {
							  same_name = true;
                              return;
						   }
					    }
                        catch (const string &caught) {
                           cerr << caught << endl;
                           throw;
                        }
					   
                        connex_is_ok = true;
                        return;
                     }
                     if(button_no->eval(event))
                        return;
                  }
               break;
					
               case SDL_KEYDOWN:
					
                  if(event.key.keysym.sym == SDLK_DOWN) {
                     id_input<2?id_input++:id_input=0;
                     y_input = Y_INPUT + id_input * LINES_SPACE;
                     textinput->get(NULL, image, X_INPUT, y_input);
                     break;
                  }
						
                  if(event.key.keysym.sym == SDLK_UP) {
                     id_input>0?id_input--:id_input=2;
                     y_input = Y_INPUT + id_input * LINES_SPACE;
                     textinput->get(NULL, image, X_INPUT, y_input);
                     break;
                  }

                  if(completed == false)
                     if(!textinput->get(&event, image, X_INPUT, y_input)) {
                        id_input<2?id_input++:id_input=0;

                        switch(id_input) {

                           case 1:
                              login = textinput->text();
                              cout << "login : " << login << endl;
                              y_input = Y_INPUT + id_input * LINES_SPACE;
                              textinput->get(NULL, image, X_INPUT, y_input);
                           break;

                           case 2:

                              passwd = textinput->text();
                              cout << "passwd : " << passwd << endl;
                              y_input = Y_INPUT + id_input * LINES_SPACE;
                              textinput->get(NULL, image, X_INPUT, y_input);
                           break;

                           case 0:

                              name_tama = textinput->text();
                              completed = true;
                              cout << "name of tamagotchi : " << name_tama << endl;
                              button_yes->show();
                              button_no->show();

                              SDL_BlitSurface(text_surface, NULL, image, &dest_text);
                           break;
                        }
                  }
                  break;
				
                  case SDL_QUIT:
                     file.close();
                     TTF_CloseFont(font);
                     TTF_Quit();
                     SDL_FreeSurface(text_surface);
                     exit(0);
				}
           }
		}
	}
}

bool Connexion::connected(void) {
	return connex_is_ok;
}

bool Connexion::duplecated_login(void) {
	return same_name;
}
