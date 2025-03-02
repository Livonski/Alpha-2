#include "Tile.h"

#include "raylib.h"
#include <iostream>

Tile::Tile() {};

Tile::Tile(int tileIndex, bool isWalkable) {
	this->tileIndex  = tileIndex;
	this->isWalkable = isWalkable;
	this->entities = {};
}

void Tile::AddEntity(int ID) {
	//isWalkable = false;
	entities.push_back(ID);
}

void Tile::RemoveEntity(int ID) {
	auto it = std::find(entities.begin(), entities.end(), ID);
	if (it != entities.end()) {
		entities.erase(it);
	}
}

bool Tile::OccupiedByEntity() {
	return entities.size() > 0;
}

bool Tile::OccupiedByEntity(int ID) {
	for (auto entity : entities) {
		if (entity == ID)
			return true;
	}
	return false;
}
