#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include <RapidXML\rapidxml.hpp>
#include <RapidXML\rapidxml_iterators.hpp>
#include <RapidXML\rapidxml_print.hpp>
#include <RapidXML\rapidxml_utils.hpp>

#include "Tile.h"
#include "Map.h"



using namespace std;
using namespace rapidxml;

bool inizializza();
SDL_Texture* caricaMedia(char*);
void chiudi();
SDL_Texture* caricaTexture(char*);

int LARGHEZZA_SCHERMO = 1024;
int ALTEZZA_SCHERMO = 768;
int GRANDEZZA_TEXTURE = 48;
SDL_Window* gFinestra = NULL; 
SDL_Renderer* gRenderizzatore = NULL;
SDL_Texture* gTexture = NULL;







int main( int argc, char* args[] )
{
	bool esci = false;
	SDL_Event e;
	inizializza();
	const int nc = 300,nr = 300;
	SDL_Texture* textQwe = NULL;
	SDL_Texture* missing_texture= NULL;

	int CX=-((LARGHEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2),CY=-((ALTEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2);
	

	xml_document<> doc;
	ifstream file("xml_file.xml");
	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);



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
	SDL_Rect textures[7][4]={
		{0,0,16,16},
		{16,0,16,16},
		{32,0,16,16},
		{48,0,16,16},
		{80,0,16,16},
		{96,0,16,16},
		{112,0,16,16}
	};

	//Sistema di mappatura semi-definitivo, ora riempito in maniera random tanto per
	Tile* mappa2[nr][nc]={
		{new Map(GRANDEZZA_TEXTURE,false,textQwe,gRenderizzatore,textures[2]),new Map(GRANDEZZA_TEXTURE,false,textQwe,gRenderizzatore,textures[5])},
		{new Map(GRANDEZZA_TEXTURE,false,textQwe,gRenderizzatore,textures[6]),new Map(GRANDEZZA_TEXTURE,false,textQwe,gRenderizzatore,textures[0])}
	};
	int o,p;
	for(o = 0; o< nr; o++)
		for(p = 0; p<nc; p++)
			mappa2[o][p] = new Map(GRANDEZZA_TEXTURE,false,textQwe,gRenderizzatore,textures[(rand()%7)]);


	while(!esci) {
		if(SDL_PollEvent( &e ) ){
			if( e.type == SDL_QUIT ) 
				esci = true;  

			if (e.type == SDL_KEYDOWN)
			{
				SDL_Keycode keyPressed = e.key.keysym.sym;
				switch (keyPressed)
				{
				case SDLK_w:
					if(CY > -((ALTEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2))
						CY--;
					break;
				case SDLK_s:
					if(CY < nr-((ALTEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2)-1)
						CY++;
					break;
				case SDLK_a:
					if(CX > -((LARGHEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2))
						CX--;
					break;
				case SDLK_d:
					if(CX < nc-((LARGHEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2)-1)
						CX++;
					break;
				}
				printf("CX: %d\tCY: %d\n",CX,CY);
			}
		}


		SDL_SetRenderDrawColor( gRenderizzatore, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear( gRenderizzatore );
		int i= 0,j = 0,x=-GRANDEZZA_TEXTURE*CX,y=-GRANDEZZA_TEXTURE*CY;

		for(;i < nr; i++){
			j = 0;
			x = -GRANDEZZA_TEXTURE*CX;
			for(; j < nc; j++){	

				//Metodo 1: uso un array che contiene le corrds delle textures nell'atlas
				/*
				SDL_Rect fillRect = {x,y,GRANDEZZA_TEXTURE,GRANDEZZA_TEXTURE}; 
				SDL_RenderCopy(gRenderizzatore,textQwe,textures[mappa[i][j]],&fillRect);
				*/

				//Nuovo brillante metodo all in one
				mappa2[i][j]->Renderizza(x,y);
				x += GRANDEZZA_TEXTURE;
			}
			y += GRANDEZZA_TEXTURE;
		}
		SDL_Rect asd = {((LARGHEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2)*GRANDEZZA_TEXTURE,(((ALTEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2)*GRANDEZZA_TEXTURE)+GRANDEZZA_TEXTURE-8,8,8};
		SDL_RenderCopy(gRenderizzatore,missing_texture,NULL,&asd);

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