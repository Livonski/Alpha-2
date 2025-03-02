#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include <vector>

class Tile {
public:
	bool isWalkable;
	int tileIndex;
	std::vector<int> entities;

	Tile();
	Tile(int tileIndex, bool isWalkable);
	void AddEntity(int ID);
	void RemoveEntity(int ID);
	bool OccupiedByEntity();
	bool OccupiedByEntity(int ID);
};

#endif
