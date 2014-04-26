#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>


using namespace std;
bool inizializza();
bool caricaTexturePNG(char*);
SDL_Texture* caricaMedia(char*);
void chiudi();
SDL_Texture* caricaTexture(char*);

int LARGHEZZA_SCHERMO = 800;
int ALTEZZA_SCHERMO = 600;
SDL_Window* gFinestra = NULL; 
SDL_Renderer* gRenderizzatore = NULL;
SDL_Texture* gTexture = NULL;

int main( int argc, char* args[] )
{
	bool esci = false;
	SDL_Event e;
	inizializza();
	int nr,nc,x=0,y=0,sprite;
	nc = 50;
	nr = 50;
	
	SDL_Texture* textLol = NULL;
	SDL_Texture* textAsd = NULL;
	SDL_Texture* textQwe = NULL;

	textLol = caricaMedia("../Textures/brick.png");
	textAsd = caricaMedia("../Textures/lava_flow.png");
	textQwe = caricaMedia("../Textures/terrain.jpg");

	SDL_Rect txt1 = {0,0,16,16};
	SDL_Rect txt2 [512];

	for(sprite = 0;sprite <512; sprite++){
		txt2[sprite].x = 0;
		txt2[sprite].y = sprite;
		txt2[sprite].h = 16;
		txt2[sprite].w = 16;
	}

		int frame = 0;

	while(!esci) {
		while(SDL_PollEvent( &e ) != 0 )
			if( e.type == SDL_QUIT ) 
				esci = true;  

		SDL_SetRenderDrawColor( gRenderizzatore, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderizzatore );
		int i= 0;
		bool test = true;
		y = 0;
		/*
		for(;i < nr ; i++){
			x = 0;
			j = 0;
			for(; j < nc; j++){	
					if (test){
						SDL_Rect fillRect = {x,y,16,16}; 
						SDL_RenderCopy(gRenderizzatore,textQwe,&txt1,&fillRect);
						SDL_RenderDrawRect(gRenderizzatore,NULL);
						
					}else{*/
						SDL_Rect fillRect = {x,y,128,128};
						SDL_Rect* currentClip = &txt2[frame /32];
						SDL_RenderCopy(gRenderizzatore,textAsd,currentClip,&fillRect);
						SDL_RenderDrawRect(gRenderizzatore,&fillRect);
						if(frame == 511)
							frame = 0;
						else
							frame++;/*
					}
					test = !test;
					x = x+16;
				}
				
			y = y+16;
		}*/
		SDL_RenderPresent( gRenderizzatore );
	}
	SDL_DestroyTexture(textLol); 	
	SDL_DestroyTexture(textAsd);
	SDL_DestroyTexture(textQwe);
	textLol = NULL;
	textAsd = NULL;
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

bool caricaTexturePNG(char* percorso){
	bool flag = true;
	gTexture = IMG_LoadTexture(gRenderizzatore,percorso);
	if (gTexture == NULL){
		printf("Immagine non trovata!");
		flag = false;
	}
	return flag;
}