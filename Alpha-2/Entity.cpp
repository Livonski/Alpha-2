#include "GlobalConsts.h"
#include "Entity.h"
#include "raylib.h"
#include "Heatmaps.h"
#include "Map.h"
#include "Entities.h"

#include <iostream>

Entity::Entity(int ID, std::string name, int maxHP, double regeneration, int damage, Vector2 position, int tileIndex, Color color) {
	this->ID = ID;
	this->name = name;
	this->maxHP = maxHP;
	this->HP = maxHP;
	this->regeneration = regeneration;
	this->regenerationBuffer = 0;
	this->damage = damage;
	this->position = position;
	this->tileIndex = tileIndex;
	this->direction = { 0,0 };
	this->color = color;
}

void Entity::CalculateTurn() {
	//int bestScore = INT16_MAX;
	int bestScore = GetPlayerHeatmapTile(position.x, position.y);
	Vector2 bestDirection = { 0, 0 };
	for (int y = position.y - 1; y <= position.y + 1; y++) {
		for (int x = position.x - 1; x <= position.x + 1; x++) {
			if (x < 0 || y < 0 || x > WORLD_WIDTH || y > WORLD_HEIGHT)
				continue;
			if (x == position.x && y == position.y)
				continue;
			if (IsOccupiedByEntity(x, y) && !IsOccupiedByEntity(x, y, 0))
				continue;
			
			int heatmapValue = GetPlayerHeatmapTile(x, y);

			if (heatmapValue == -1)
				continue;

			if (heatmapValue < bestScore) {
				bestDirection = {x - position.x, y - position.y};
				bestScore = heatmapValue;
			}
		}
	}

	direction = bestDirection;
	EntityMove(direction, ID);
}

void Entity::OnTurnEnd() {
	if(HP < maxHP)
		regenerationBuffer += regeneration;
	if (regenerationBuffer >= 1) {
		HP = std::min(maxHP, HP + (int)regenerationBuffer);
		regenerationBuffer = 0;
	}
}