#include "Entities.h"
#include "Entity.h"
#include "Map.h"
#include "GlobalConsts.h"
#include "Heatmaps.h"

#include "raylib.h"
#include <iostream>
#include <vector>

std::vector<Entity> entities;

Entity player({0,0}, TILE_INDEX_PLAYER, WHITE);

Vector2 ladderPosition;


void AddEntity(Vector2 pos, int tileIndex, Color color) {
	Entity newEntity(pos, tileIndex, color);
	entities.push_back(newEntity);
}

void EntitiesClear() {
	entities.clear();
}

std::vector<Entity> EntitiesGet() {
	return entities;
}

void EntitiesCalculateTurns() {
	for (int i = 0; i < entities.size(); i++) {
		entities[i].CalculateTurn();
	}
}

void PlayerPositionSet(int x, int y) {
	player.position = { (float)x, (float)y };
	OnPlayerMove(player.position);
}

Vector2 PlayerPositionGet() {
	return player.position;
}

void LadderPositionSet(int x, int y) {
	ladderPosition = { (float)x, (float)y };
}

Vector2 LadderPositionGet() {
	return ladderPosition;
}

void PlayerMove(Vector2 direction) {
	if (direction.x == 0 && direction.y == 0)
		return;

	Vector2 newPosition = { player.position.x + direction.x, player.position.y + direction.y };

	if (newPosition.x < 0 || newPosition.x > WORLD_WIDTH ||
		newPosition.y < 0 || newPosition.y > WORLD_HEIGHT) {
		throw std::runtime_error("Entities, PlayerMove, trying to move player outside of map bounds");
		return;
	}

	if(!IsMovable(newPosition.x, newPosition.y)) {
		return;
	}

	player.position = newPosition;
	OnPlayerMove(player.position);
}