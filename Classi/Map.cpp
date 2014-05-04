
#include "Map.h"


Map::Map(int x, int y,int grandezza,bool solido,SDL_Texture* texture,SDL_Renderer* renderizzatore,SDL_Rect* tile) {
	SDL_Rect tmp = {x*grandezza,y*grandezza,grandezza,grandezza};
	Map::parte = tmp;
	Map::texture = texture;
	Map::renderizzatore = renderizzatore;
	Map::tile = tile;
	Map::solido = solido;
}

Map::~Map() {
	texture = NULL;
	renderizzatore = NULL;
	tile = NULL;
}

int Map::getTipo(){
	return 1;
}

void Map::Renderizza(){
	SDL_RenderCopy(renderizzatore,texture,tile,&parte);
}

bool Map::solid(){
	return solido;
}
