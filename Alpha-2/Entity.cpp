#include "GlobalConsts.h"
#include "Entity.h"
#include "raylib.h"
#include "Heatmaps.h"

#include <iostream>

Entity::Entity(Vector2 position, int tileIndex, Color color) {
	this->position = position;
	this->tileIndex = tileIndex;
	this->color = color;
}

void Entity::CalculateTurn() {
	int bestScore = INT16_MAX;
	Vector2 bestDirection = { 0, 0 };
	for (int y = position.y - 1; y <= position.y + 1; y++) {
		for (int x = position.x - 1; x <= position.x + 1; x++) {
			//std::cout << "currentPos: " << x << " : " << y << ", bestScore: " << bestScore << ", current score: " << GetPlayerHeatmapTile(x, y) << std::endl;
			
			if (x < 0 || y < 0 || x > WORLD_WIDTH || y > WORLD_HEIGHT)
				continue;
			if ((x == position.x && y == position.y) || GetPlayerHeatmapTile(x, y) == -1)
				continue;

			if (GetPlayerHeatmapTile(x, y) < bestScore) {
				bestDirection = {x - position.x, y - position.y};
				bestScore = GetPlayerHeatmapTile(x, y);
			}
		}
	}

	//std::cout << "direction: " << bestDirection.x << " : " << bestDirection.y << ", position: " << position.x << " : " << position.y << std::endl;
	direction = bestDirection;
	position.x += direction.x;
	position.y += direction.y;
}