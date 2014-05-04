
#ifndef TILE_H_
#define TILE_H_

#include <SDL2\SDL.h>

class Tile {
	public:
		Tile();
		virtual ~Tile();
		virtual int getTipo() = 0;
		virtual void Renderizza() = 0;
};

#endif /* TILE_H_ */
