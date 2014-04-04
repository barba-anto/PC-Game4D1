
#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "Tile.h"

class Entities: public virtual Tile {
	public:
		Entities();
		virtual ~Entities();
		int getTipo();
		int getStato();
		//Tool* inventario();
};

#endif /* ENTITIES_H_ */
