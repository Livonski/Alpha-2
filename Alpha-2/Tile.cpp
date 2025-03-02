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
	isWalkable = false;
	entities.push_back(ID);
}

void Tile::RemoveEntity(int ID) {
	isWalkable = true;
	auto it = std::find_if(entities.begin(), entities.end(), [ID](const int foundID) {
		return foundID == ID;
	});

	if (it != entities.end()) {
		entities.erase(it);
	}
	else {
		throw std::runtime_error("Tile, RemoveEntity, trying to remove entity that doesn't exist");
	}
}
