
#include "Entities.h"

Entities::Entities(int grandezza,bool solido,SDL_Texture* texture,SDL_Renderer* renderizzatore,SDL_Rect* tile, int frame, char* contenuto) {
	Entities::dimensione = grandezza;
	Entities::texture = texture;
	Entities::renderizzatore = renderizzatore;
	Entities::tile = tile;
	Entities::solido = solido;
	Entities::frame = frame;
	Entities::frame_attuale = 0;
	SDL_strlcpy(Entities::contenuto,contenuto,SDL_strlen(contenuto));
}

Entities::~Entities() {
	texture = NULL;
	renderizzatore = NULL;
	tile = NULL;
}

int Entities::getTipo(){
	return 2;
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
