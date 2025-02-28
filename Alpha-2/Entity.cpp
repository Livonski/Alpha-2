#include "Entity.h"
#include "raylib.h"

Entity::Entity(Vector2 position, int tileIndex, Color color) {
	this->position = position;
	this->tileIndex = tileIndex;
	this->color = color;
}