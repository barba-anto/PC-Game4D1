#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

bool inizializza();

void chiudi();

int LARGHEZZA_SCHERMO = 800;
int ALTEZZA_SCHERMO = 600;
SDL_Window* gFinestra = NULL; 
SDL_Surface* gSuperficie = NULL; 

int main( int argc, char* args[] )
{
	inizializza();




	chiudi();
	return 0;
}

bool inizializza() { 
	bool flag = true; 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
		printf( "Non è stato possibile istanziare SDL; errore: %s\n", SDL_GetError() ); 
		flag = false; 
	} 
	else { 
		gFinestra = SDL_CreateWindow( "Prova Tile", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGHEZZA_SCHERMO, ALTEZZA_SCHERMO, SDL_WINDOW_SHOWN ); 
		if( gFinestra == NULL ) { 
			printf( "Non è stato possiblile creare la finestra; errore: %s\n", SDL_GetError() );
			flag = false; 
		}
		else { 
			gSuperficie = SDL_GetWindowSurface( gFinestra ); 
		} 
	} 
	return flag; 
}

void chiudi() { 
	SDL_DestroyWindow( gFinestra );
	gFinestra = NULL;  
	SDL_Quit();
}