#!/bin/sh

#export LD_LIBRARY_PATH="/usr/lib:/usr/local/lib"

g++ -lSDL_ttf -lSDL_image -L/usr/local/lib/mysql -L/usr/local/lib -I/usr/include/mysql -I/usr/include/mysql++ -lmysqlclient -lmysqlpp sql.cpp draw.cpp timeleft.cpp button.cpp textinput.cpp connexion.cpp showBMP.cpp tamagotchi.cpp -o ../tamagotchi -lGL $(sdl-config --cflags --libs) 
