#ifndef ENTITIES_H
#define ENTITIES_H

#include "Entity.h"

#include "raylib.h"
#include <unordered_map>

void AddEntity(Vector2 pos, int tileIndex, Color color);
void EntitiesClear();
std::unordered_map<int, Entity*> EntitiesGet();

void EntitiesCalculateTurns();
void EntitiesOnTurnEnd();

void PlayerPositionSet(int x, int y);
Vector2 PlayerPositionGet();

void LadderPositionSet(int x, int y);
Vector2 LadderPositionGet();

void EntityMove(Vector2 direction, int ID);

#endif
