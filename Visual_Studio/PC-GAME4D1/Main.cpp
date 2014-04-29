#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "Tile.h"
#include "Map.h"



using namespace std;
bool inizializza();
SDL_Texture* caricaMedia(char*);
void chiudi();
SDL_Texture* caricaTexture(char*);

int LARGHEZZA_SCHERMO = 800;
int ALTEZZA_SCHERMO = 600;
int GRANDEZZA_TEXTURE = 128;
SDL_Window* gFinestra = NULL; 
SDL_Renderer* gRenderizzatore = NULL;
SDL_Texture* gTexture = NULL;


int main( int argc, char* args[] )
{
	bool esci = false;
	SDL_Event e;
	inizializza();
	int x=0,y=0;
	const int nc = 16,nr = 8;


	SDL_Texture* textQwe = NULL;
	SDL_Texture* missing_texture= NULL;


	textQwe = caricaMedia("../../Textures/Textures.png");

	//Quando la texture manca...
	missing_texture = caricaMedia("../../Textures/MISSING_TEXTURE_0x00000000.png");

	/*
	//Metodo 1:coordinate delle textures nell'atlas 
	SDL_Rect a={32,0,16,16};
	SDL_Rect b={16,0,16,16};
	SDL_Rect c={64,0,16,16};
	SDL_Rect d={0,16,16,16};

	SDL_Rect* textures[4]={&a,&b,&c,&d};
	*/

	//Metodo di riempimeto più efficace
	SDL_Rect textures[8][4]={
		{0,0,16,16},
		{16,0,16,16},
		{32,0,16,16},
		{48,0,16,16},
		{64,0,16,16},
		{80,0,16,16},
		{96,0,16,16},
		{112,0,16,16}
	};

	//Sistema di mappatura semi-definitivo
	Tile* mappa2[2][2]={
		{new Map(0,0,GRANDEZZA_TEXTURE,textQwe,gRenderizzatore,textures[2]),new Map(0,1,GRANDEZZA_TEXTURE,textQwe,gRenderizzatore,textures[5])},
		{new Map(1,0,GRANDEZZA_TEXTURE,textQwe,gRenderizzatore,textures[6]),new Map(1,1,GRANDEZZA_TEXTURE,textQwe,gRenderizzatore,textures[0])}
	};


	while(!esci) {
		while(SDL_PollEvent( &e ) != 0 )
			if( e.type == SDL_QUIT ) 
				esci = true;  

		SDL_SetRenderDrawColor( gRenderizzatore, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear( gRenderizzatore );
		int i= 0;
		y = 0;
		int j = 0;

		for(;i < 2 ; i++){
			x = 0;
			j = 0;
			for(; j < 2; j++){	
				
				//Metodo 1: uso un array che contiene le corrds delle textures nell'atlas
				/*
				SDL_Rect fillRect = {x,y,GRANDEZZA_TEXTURE,GRANDEZZA_TEXTURE}; 
				SDL_RenderCopy(gRenderizzatore,textQwe,textures[mappa[i][j]],&fillRect);
				*/

				//Nuovo brillante metodo all in one
				mappa2[i][j]->Renderizza();


				x = x+GRANDEZZA_TEXTURE;
			}
			y = y+GRANDEZZA_TEXTURE;
		}
		SDL_RenderPresent( gRenderizzatore);
		
	}

	SDL_DestroyTexture(textQwe);
	textQwe = NULL;
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
			gRenderizzatore = SDL_CreateRenderer(gFinestra,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
			SDL_SetRenderDrawColor(gRenderizzatore,0xFF,0xFF,0xFF,SDL_ALPHA_OPAQUE);
			int imgF = IMG_INIT_PNG;
			if( !( IMG_Init( imgF ) & imgF ) ) {
				printf( "Impossibile caricare l'immagine, errore: %s\n", IMG_GetError() ); 
				flag = false; 
			}
		} 
	} 
	return flag; 
}
SDL_Texture* caricaMedia(char* percorso) {
	SDL_Texture* text;
	text = caricaTexture(percorso); 
	if( text == NULL ) { 
		printf( "Failed to load texture image!\n" ); 
	} 
	return text;
}



void chiudi() { 
	SDL_DestroyTexture( gTexture ); 
	gTexture = NULL;

	SDL_DestroyRenderer( gRenderizzatore );
	SDL_DestroyWindow( gFinestra );
	gFinestra = NULL;
	gRenderizzatore = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* caricaTexture(char* percorso){

	SDL_Texture* tmp = NULL;
	SDL_Surface* sCarica = IMG_Load(percorso);

	if(sCarica	==	NULL)
		printf( "Impossibile trovare l'immagine, errore: %s\n", IMG_GetError() ); 
	else{
		tmp = SDL_CreateTextureFromSurface(gRenderizzatore,sCarica);
		if(tmp == NULL)
			printf( "Impossibile texturizzare l'immagine, errore: %s\n", IMG_GetError() );

		SDL_FreeSurface(sCarica);
	}
	return tmp;
}