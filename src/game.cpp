#include "game.hpp"

#include <stdio.h>

#include "SDL/SDL.h"

int main( int argc, char*argv[] ){

	printf( "\nHello World\n\n" );
	//Start SDL
	SDL_Init( SDL_INIT_EVERYTHING );



	//Quit SDL
	SDL_Quit();



	return 0;
}
