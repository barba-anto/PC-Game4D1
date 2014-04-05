#ifndef WEAPON_H_
#define WEAPON_H_

#include "Tool.h"

class Weapon: public virtual Tool {
	public:
		Weapon();
		virtual ~Weapon();
		void Usa();
};

#endif /* WEAPON_H_ */
