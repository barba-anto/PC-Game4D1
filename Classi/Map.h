
#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"

class Map: public virtual Tile {
	public:
		Map(int x, int y,int grandezza,SDL_Texture* texture,SDL_Renderer* renderizzatore,SDL_Rect* tile);
		virtual ~Map();
		int getTipo();
		bool canPass();
		int getModalita();
		void Renderizza();
	private:
		SDL_Rect parte;
		SDL_Texture* texture;
		SDL_Renderer* renderizzatore;
		SDL_Rect* tile;
};

#endif /* MAP_H_ */
