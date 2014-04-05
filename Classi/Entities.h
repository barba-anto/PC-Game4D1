
#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "Tile.h"
#include "Tool.h"

class Entities: public virtual Tile {
	public:
		Entities();
		virtual ~Entities();
		int getTipo();
		int getStato();
		Tool* getInventario();
};

#endif /* ENTITIES_H_ */
