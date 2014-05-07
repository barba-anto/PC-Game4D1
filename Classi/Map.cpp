
#include "Map.h"


Map::Map(int grandezza,bool solido,SDL_Texture* texture,SDL_Renderer* renderizzatore,SDL_Rect* tile) {
	Map::dimensione = grandezza;
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

void Map::Renderizza(int x, int y){
	SDL_Rect a = {x,y,dimensione,dimensione};
	SDL_RenderCopy(renderizzatore,texture,tile,&a);
}

bool Map::solid(){
	return solido;
}
