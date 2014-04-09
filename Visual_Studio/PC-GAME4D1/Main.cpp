#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;
bool inizializza();
bool caricaTexturePNG(char*);
void chiudi();
SDL_Texture* CaricaTexture(char*);

int LARGHEZZA_SCHERMO = 800;
int ALTEZZA_SCHERMO = 800;
SDL_Window* gFinestra = NULL; 
SDL_Renderer* gRenderizzatore = NULL;
SDL_Texture* gTexture = NULL;


int main( int argc, char* args[] )
{
	bool esci = false;
	SDL_Event e;
	inizializza();
	int r,c,nr,nc,x=0,y=0;
	nc = 800;
	nr = 800;

	r = ALTEZZA_SCHERMO/nr;
	c = LARGHEZZA_SCHERMO/nc;
	while(!esci) {
		while(SDL_PollEvent( &e ) != 0 )
			if( e.type == SDL_QUIT ) 
				esci = true;  

		SDL_SetRenderDrawColor( gRenderizzatore, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderizzatore );
		int i= 0,j;
		bool lol = true;
		y = 0;
		for(;i < nr ; i++){
			x = 0;
			j = 0;
			for(; j < nc; j++){	
				lol = !lol;
				if(lol){
					SDL_Rect fillRect = {x,y,c,r}; 
					SDL_SetRenderDrawColor( gRenderizzatore, ((rand()%(255-0))+255), ((rand()%(255-0))+255),((rand()%(255-0))+255), 0xFF );
					SDL_RenderFillRect( gRenderizzatore, &fillRect );
				}
				else
				{
					SDL_Rect fillRect = {x,y,c,r}; 
					SDL_SetRenderDrawColor( gRenderizzatore, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderFillRect( gRenderizzatore, &fillRect );
				}
				x = x+ c;
			}
			y = y+c;
		}
		SDL_RenderPresent( gRenderizzatore );
	}
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
			gRenderizzatore = SDL_CreateRenderer(gFinestra,-1,SDL_RENDERER_ACCELERATED);
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

void chiudi() { 
	SDL_DestroyRenderer( gRenderizzatore );
	SDL_DestroyWindow( gFinestra );
	gFinestra = NULL;
	gRenderizzatore = NULL;
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* CaricaTexture(char* percorso){
	
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

bool caricaTexturePNG(char* percorso){
	bool flag = true;
	gTexture = IMG_LoadTexture(gRenderizzatore,percorso);
	if (gTexture == NULL){
		printf("Immagine non trovata!");
		flag = false;
	}
	return flag;
}