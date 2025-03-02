#include "Entities.h"
#include "Entity.h"
#include "Map.h"
#include "GlobalConsts.h"
#include "Heatmaps.h"

#include "raylib.h"
#include <iostream>
#include <vector>

int maxID = 1;
std::vector<Entity> entities;
//Entity player(0, {0,0}, TILE_INDEX_PLAYER, WHITE);

Vector2 ladderPosition;


void AddEntity(Vector2 pos, int tileIndex, Color color) {
	Entity newEntity(maxID, pos, tileIndex, color);
	entities.push_back(newEntity);
	maxID++;
}

void EntitiesClear() {
	entities.clear();
}

std::vector<Entity> EntitiesGet() {
	return entities;
}

void EntitiesCalculateTurns() {
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i].ID == 0)
			continue;
		entities[i].CalculateTurn();
	}
}

void PlayerPositionSet(int x, int y) {
	Entity player(0, { (float)x, (float)y }, TILE_INDEX_PLAYER, WHITE);
	entities.push_back(player);
	OnPlayerMove(player.position);
}

Vector2 PlayerPositionGet() {
	for (auto& entity : entities) {
		if (entity.ID == 0)
			return entity.position;
	}
}

void LadderPositionSet(int x, int y) {
	ladderPosition = { (float)x, (float)y };
}

Vector2 LadderPositionGet() {
	return ladderPosition;
}

void EntityMove(Vector2 direction, int ID) {
	if (direction.x == 0 && direction.y == 0)
		return;

	bool found = false;
	for (auto& entity : entities) {
		if (entity.ID == ID) {
			found = true;
			Vector2 newPosition = { entity.position.x + direction.x, entity.position.y + direction.y };
			if (ID == 0)
				std::cout << "direction: " << direction.x << " : " << direction.y << ", position: " << entity.position.x << " : " << entity.position.y << ", newPosition: " << newPosition.x << " : " << newPosition.y << std::endl;

			if (newPosition.x < 0 || newPosition.x > WORLD_WIDTH ||
				newPosition.y < 0 || newPosition.y > WORLD_HEIGHT) {
				throw std::runtime_error("Entities, EntityMove, trying to move entity outside of map bounds");
				return;
			}
	
			if (!IsMovable(newPosition.x, newPosition.y)) 
				return;
			
			entity.position = newPosition;

			if (entity.ID == 0) 
				OnPlayerMove(entity.position);
			break;
		}
	}

	if (!found) {
		std::cerr << "Entities, EnityMove, Entity with ID " << ID << " not found" << std::endl;
	}
}

/*void PlayerMove(Vector2 direction) {
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
}*/