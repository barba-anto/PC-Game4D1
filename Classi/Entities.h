
#ifndef ENTITIES_H_
#define ENTITIES_H_

#include "Tile.h"
#include "Tool.h"

class Entities: public virtual Tile {
public:
	Entities(int,bool,SDL_Texture*,SDL_Renderer*,SDL_Rect*,int,char*,char*);
	virtual ~Entities();
	int getStato();
	Tool* getInventario();
	void Renderizza(int,int);
	bool solid();
	int getFrame();
	void setFrame(int);
	char* getTipo();
	char* getContenuto();

private:
	bool solido;
	int dimensione;
	int frame;
	int frame_attuale;
	SDL_Texture* texture;
	SDL_Renderer* renderizzatore;
	SDL_Rect* tile;
	char* tipo;
	char* contenuto;
};

#endif /* ENTITIES_H_ */
