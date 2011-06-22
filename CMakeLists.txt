cmake_minimum_required(VERSION 2.6)

project(tamagotchi)

find_package(SDL REQUIRED)

include_directories(
	${SDL_INCLUDE_DIR}
	/usr/include/mysql
	/usr/include/mysql++
)

link_directories(
	/usr/local/lib/mysql
	/usr/local/lib
)

set(
	CMAKE_CXXFLAGS "sdl-config --cflags --libs"
)

add_executable(
	tamagotchi
	sources/button.cpp
	sources/draw.cpp
	sources/showBMP.cpp
	sources/sql.h
	sources/textinput.h
	sources/button.h
	sources/draw.h
	sources/showBMP.h
	sources/tamagotchi.cpp
	sources/timeleft.cpp
	sources/connexion.cpp
	sources/tamagotchi.sh
	sources/timeleft.h
	sources/connexion.h
	sources/sql.cpp
	sources/textinput.cpp
)

TARGET_LINK_LIBRARIES(
	tamagotchi
	SDL_ttf
	SDL_image
	GL
	mysqlclient
	mysqlpp
)
