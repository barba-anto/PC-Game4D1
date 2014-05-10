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
const int NUMERO_TEXTURES = 7;
const int NUMERO_TEXTURES_DYN = 4;
const int VELOCITA = 20;
SDL_Window* gFinestra = NULL; 
SDL_Renderer* gRenderizzatore = NULL;
SDL_Texture* gTexture = NULL;







int main( int argc, char* args[] )
{
	bool esci = false;
	SDL_Event e;
	inizializza();
	SDL_Texture* textQwe = NULL;
	SDL_Texture* textDyn = NULL;
	SDL_Texture* missing_texture= NULL;
	int oX =-((LARGHEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2),oY = -((ALTEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2);

	textQwe = caricaMedia("../../Textures/Textures.png");
	textDyn = caricaMedia("../../Textures/Textures_flow.png");

	//Quando la texture manca...
	missing_texture = caricaMedia("../../Textures/MISSING_TEXTURE_0x00000000.png");

	//Metodo di riempimeto più efficace
	SDL_Rect textures[NUMERO_TEXTURES][4]={
		{0,0,16,16},
		{16,0,16,16},
		{32,0,16,16},
		{48,0,16,16},
		{80,0,16,16},
		{96,0,16,16},
		{112,0,16,16}
	};

	int textures_dyn[NUMERO_TEXTURES_DYN]={
		0,
		1,
		2,
		3
	};






	xml_document<> doc;
	ifstream file("../../XML/prova.xml");
	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	xml_node<> *nodo = doc.first_node(doc.first_node()->name());
	xml_attribute<> *attributo;
	attributo = nodo->first_attribute("altezza");

	const int nc = atoi(nodo->first_attribute("larghezza")->value());
	const int nr = atoi(nodo->first_attribute("altezza")->value());

	//Sistema di mappatura semi-definitivo, ora riempito in maniera random tanto per
	Tile* mappa[300][300][2];

	int v1,v2;
	for(v1 = 0; v1 < nr; v1 ++){
		for(v2 = 0; v2 < nc; v2 ++){
			mappa[v1][v2][0] = NULL;
			mappa[v1][v2][1] = NULL;
		}
	}



	xml_node<> *nodo2 = nodo->first_node();
	nodo2 = nodo2->next_sibling();

	int CX=atoi(nodo2->first_attribute("start_X")->value())-((LARGHEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2),CY=atoi(nodo2->first_attribute("start_Y")->value())-((ALTEZZA_SCHERMO/GRANDEZZA_TEXTURE)/2);
	int txt_id = NULL;
	int txt_frm = NULL;
	bool solid = NULL;



	xml_node<> *riga = nodo2->first_node();
	xml_node<> *colonna;
	xml_node<> *blocco;
	for(v1 = 0; v1 < nr; v1++){
		colonna = riga->first_node();
		for(v2 = 0;v2 <nc; v2++){
			blocco = colonna->first_node();
			blocco = blocco->first_node("texture_id");


			txt_id = atoi(blocco->value());
			if(blocco->next_sibling("texture_frame") != NULL){
				blocco = blocco->next_sibling("texture_frame");
				txt_frm = atoi(blocco->value());
			}

			blocco = blocco->next_sibling("solido");
			if(strcmp(blocco->value(),"true"))
				solid = false;
			else
				solid = true;

			if(txt_frm != NULL){
				printf("X:%d Y:%d\ttxt_id:%d txt_frm:%d\n",v1,v2,txt_id,txt_frm);
				mappa[v1][v2][0] = new Map(GRANDEZZA_TEXTURE,solid,textDyn,gRenderizzatore,textures_dyn[txt_id],txt_frm,VELOCITA);
			}
			else{
				printf("X:%d Y:%d\ttxt_id:%d\n",v1,v2,txt_id);
				mappa[v1][v2][0] = new Map(GRANDEZZA_TEXTURE,solid,textQwe,gRenderizzatore,textures[txt_id]);
			}
			txt_id= 0;
			txt_frm = 0;
			solid = 0;

			colonna = colonna->next_sibling();
		}
		riga = riga->next_sibling();
	}

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


	/*

	int o,p;
	for(o = 0; o< nr; o++)
	for(p = 0; p<nc; p++)
	mappa[o][p][0] = new Map(GRANDEZZA_TEXTURE,false,textQwe,gRenderizzatore,textures[(rand()%7)]);
	*/

	while(!esci) {
		if(SDL_PollEvent( &e ) ){
			if( e.type == SDL_QUIT ) 
				esci = true;  

			if (e.type == SDL_KEYDOWN)
			{
				SDL_Keycode keyPressed = e.key.keysym.sym;
				printf("%d %d %d\n",(CY-oY),(CX-oX),mappa[(CY-oY)][(CX-oX)][0]->solid());
				switch (keyPressed)
				{
				case SDLK_w:
					if((CY-oY) > 0)
						if((CY-oY)-1 > -1)
							if(!mappa[(CY-oY)-1][(CX-oX)][0]->solid())
								CY--;
					break;
				case SDLK_s:
					if((CY-oY) < nr-1)
						if((CY-oY)-1 < nr)
							if(!mappa[(CY-oY)+1][(CX-oX)][0]->solid())
								CY++;
					break;
				case SDLK_a:
					if((CX-oX) > 0)
						if((CX-oX)-1 > -1)
							if(!mappa[(CY-oY)][(CX-oX)-1][0]->solid())
								CX--;
					break;
				case SDLK_d:
					if((CX-oX) < nc-1)
						if((CX-oX)-1 < nc)
							if(!mappa[(CY-oY)][(CX-oX)+1][0]->solid())
								CX++;
					break;
				}
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
				mappa[i][j][0]->Renderizza(x,y);
				if(mappa[i][j][1] != NULL)
					mappa[i][j][1]->Renderizza(x,y);
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