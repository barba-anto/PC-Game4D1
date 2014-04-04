
#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"

class Map: public virtual Tile {
	public:
		Map();
		virtual ~Map();
		int getTipo();
		bool canPass();
		int getModalita();
};

#endif /* MAP_H_ */
