
#ifndef TILE_H_
#define TILE_H_

class Tile {
	public:
		Tile();
		virtual ~Tile();
		virtual int getTipo() = 0;
};

#endif /* TILE_H_ */
