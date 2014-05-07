
#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"

class Map: public virtual Tile {
	public:
		Map(int,bool,SDL_Texture*,SDL_Renderer*,SDL_Rect*);
		virtual ~Map();
		int getTipo();
		bool solid();
		int getModalita();
		void Renderizza(int,int);
	private:
		bool solido;
		int dimensione;
		SDL_Texture* texture;
		SDL_Renderer* renderizzatore;
		SDL_Rect* tile;
};

#endif /* MAP_H_ */
