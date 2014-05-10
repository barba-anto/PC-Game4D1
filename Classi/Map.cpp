
#include "Map.h"


Map::Map(int grandezza,bool solido,SDL_Texture* texture,SDL_Renderer* renderizzatore,SDL_Rect* tile) {
	Map::dimensione = grandezza;
	Map::texture = texture;
	Map::renderizzatore = renderizzatore;
	Map::tile = tile;
	Map::solido = solido;
	Map::nframe = -1;
}
Map::Map(int grandezza,bool solido,SDL_Texture* texture,SDL_Renderer* renderizzatore,SDL_Rect* tile,int nframe ,int speed){
	Map::dimensione = grandezza;
	Map::texture = texture;
	Map::renderizzatore = renderizzatore;
	Map::tile = tile;
	Map::solido = solido;
	Map::nframe = nframe;
	Map::frame_cur = 0;
	Map::velocita = speed;
}


Map::~Map() {
	texture = NULL;
	renderizzatore = NULL;
	tile = NULL;
}

int Map::getTipo(){
	return 1;
}

void Map::Renderizza(int x, int y){
	SDL_Rect a = {x,y,dimensione,dimensione};
	if(nframe > 0){
		SDL_Rect a = {x,y,dimensione,dimensione};
		SDL_RenderCopy(renderizzatore,texture,&tile[frame_cur/velocita],&a);
		if(frame_cur == nframe)
			frame_cur = 0;
		else
			frame_cur++;
	}
	else

	SDL_RenderCopy(renderizzatore,texture,tile,&a);
}

bool Map::solid(){
	return solido;
}
