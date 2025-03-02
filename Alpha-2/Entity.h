#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

class Entity {
public:
	int ID;

	Vector2 position;
	Vector2 direction;

	int tileIndex;
	Color color;

	Entity(int ID, Vector2 position, int tileIndex, Color color);
	void CalculateTurn();
};


#endif
