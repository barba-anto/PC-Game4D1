
#include "Entities.h"
#include <stdio.h>

Entities::Entities(int grandezza,bool solido,SDL_Texture* texture,SDL_Renderer* renderizzatore,SDL_Rect* tile, int frame, char* tipo,char* contenuto) {
	Entities::dimensione = grandezza;
	Entities::texture = texture;
	Entities::renderizzatore = renderizzatore;
	Entities::tile = tile;
	Entities::solido = solido;
	Entities::frame = frame;
	Entities::frame_attuale = 0;
	Entities::tipo = (char*)SDL_malloc(SDL_strlen(tipo));
	SDL_strlcpy(Entities::tipo,tipo,sizeof(char)*(SDL_strlen(tipo)+1));
	Entities::contenuto = (char*)SDL_malloc(SDL_strlen(contenuto));
	SDL_strlcpy(Entities::contenuto,contenuto,sizeof(char*)*(SDL_strlen(contenuto)+1));
}

Entities::~Entities() {
	texture = NULL;
	renderizzatore = NULL;
	tile = NULL;
	SDL_free(Entities::contenuto);
	SDL_free(Entities::tipo);
}

void Entities::Renderizza(int x,int y){
	SDL_Rect a = {x,y,dimensione,dimensione};
	SDL_RenderCopy(renderizzatore,texture,&tile[frame_attuale],&a);
}

bool Entities::solid(){
	return solido;
}

void Entities::setFrame(int frm){
	if(frm > 0 && frm< Entities::frame)
		Entities::frame_attuale = frm;
}

int Entities::getFrame(){
	return frame_attuale;
}

char* Entities::getContenuto(){
	return Entities::contenuto;
}

char* Entities::getTipo(){
	return Entities::tipo;
}
