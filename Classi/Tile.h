
#ifndef TILE_H_
#define TILE_H_

#include <SDL2\SDL.h>

class Tile {
public:
	Tile();
	virtual ~Tile();
	virtual void Renderizza(int,int) = 0;
	virtual bool solid() = 0;
};

#endif /* TILE_H_ */
