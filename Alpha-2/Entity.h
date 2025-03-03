#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include <string>

class Entity {
public:
	int ID;
	std::string name;

	int maxHP;
	int HP;
	double regeneration;
	double regenerationBuffer;
	int damage;

	Vector2 position;
	Vector2 direction;

	int tileIndex;
	Color color;

	Entity(int ID, std::string name, int maxHP, double regeneration, int damage, Vector2 position, int tileIndex, Color color);
	void CalculateTurn();
	void OnTurnEnd();
};


#endif
