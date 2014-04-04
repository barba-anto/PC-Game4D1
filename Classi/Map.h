/*
 * Map.h
 *
 *  Created on: 04/apr/2014
 *      Author: Christian
 */

#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"

class Map: public virtual Tile {
public:
	Map();
	virtual ~Map();
};

#endif /* MAP_H_ */
