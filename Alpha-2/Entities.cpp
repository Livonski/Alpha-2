#include "Entities.h"
#include "Entity.h"
#include "Map.h"
#include "GlobalConsts.h"
#include "Heatmaps.h"

#include "raylib.h"
#include <iostream>
#include <vector>
#include <unordered_map>

int maxID = 1;
std::unordered_map<int, Entity*> entities;

Vector2 ladderPosition;


void AddEntity(Vector2 pos, int tileIndex, Color color) {
	AddEntityToTile(pos.x, pos.y, maxID);
	Entity* newEntity = new Entity(maxID, "Goblin", 10, 0, 2, pos, tileIndex, color);
	entities.emplace(maxID, newEntity);
	maxID++;
}

void EntitiesClear() {
	for (auto& pair : entities) {
		delete pair.second;
	}
	entities.clear();
}

std::unordered_map<int, Entity*> EntitiesGet() {
	return entities;
}

void EntitiesCalculateTurns() {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		if (it->first == 0)
			continue;
		it->second->CalculateTurn();
	}
}

void EntitiesOnTurnEnd() {
	for (auto it = entities.begin(); it != entities.end(); it++) {
		it->second->OnTurnEnd();
	}
}

void PlayerPositionSet(int x, int y) {
	Entity* player = new Entity(0, "Player", 20, 0.2, 5, { (float)x, (float)y }, TILE_INDEX_PLAYER, WHITE);
	entities.emplace(0, player);
	OnPlayerMove(player->position);
}

Vector2 PlayerPositionGet() {
	auto it = entities.find(0);
	if (it != entities.end())
		return it -> second -> position;
}

void LadderPositionSet(int x, int y) {
	ladderPosition = { (float)x, (float)y };
}

Vector2 LadderPositionGet() {
	return ladderPosition;
}

//Bugs:
//Sometimes entities still can move in one tile
void EntityMove(Vector2 direction, int ID) {
	if (direction.x == 0 && direction.y == 0)
		return;
	auto it = entities.find(ID);
	if (it != entities.end()) {
		Entity* entity = it->second;
		Vector2 newPosition = { entity->position.x + direction.x, entity->position.y + direction.y };

		if (newPosition.x < 0 || newPosition.x > WORLD_WIDTH ||
			newPosition.y < 0 || newPosition.y > WORLD_HEIGHT) {
			throw std::runtime_error("Entities, EntityMove, trying to move entity outside of map bounds");
			return;
		}

		if (IsOccupiedByEntity(newPosition.x, newPosition.y)) {
			int defender = GetTile(newPosition.x, newPosition.y).entities.front();
			int damage = entity->damage;
			entities[defender]->HP -= damage;
			
			std::cout << entity->name << " attacked " << entities[defender]->name << "for " << damage << " damage, " << entities[defender]->name << " remaining HP - " << entities[defender]->HP << std::endl;
			
			if (entities[defender]->HP <= 0 && defender != 0) {
				RemoveEntityFromTile(entities[defender]->position.x, entities[defender]->position.y, defender);
				entities.erase(defender);
			}
			return;
		}

		if (!IsWalkable(newPosition.x, newPosition.y))
			return;

		RemoveEntityFromTile(entity->position.x, entity->position.y, ID);
		entity->position = newPosition;
		AddEntityToTile(entity->position.x, entity->position.y, ID);

		if (entity->ID == 0)
			OnPlayerMove(entity->position);

	} else {
		std::cerr << "Entities, EnityMove, Entity with ID " << ID << " not found" << std::endl;
	}
}
