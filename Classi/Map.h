
#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"

class Map: public virtual Tile {
public:
	Map(int,bool,SDL_Texture*,SDL_Renderer*,SDL_Rect*);
	Map(int,bool,SDL_Texture*,SDL_Renderer*,int,int,int);
	virtual ~Map();
	bool solid();
	int getModalita();
	void Renderizza(int,int);
private:
	bool solido;
	int dimensione;
	int nframe;
	int frame_cur;
	int dyn_x;
	int velocita;
	SDL_Texture* texture;
	SDL_Renderer* renderizzatore;
	SDL_Rect* tile;
};

#endif /* MAP_H_ */
