#ifndef MAP_H
#define MAP_H

#include "Tile.h"

void MapGenerate();

Tile GetTile(int x, int y);
int GetTileTilesetIndex(int x, int y);
bool IsWalkable(int x, int y);
bool IsOccupiedByEntity(int x, int y);
bool IsOccupiedByEntity(int x, int y, int ID);

void AddEntityToTile(int x, int y, int ID);
void RemoveEntityFromTile(int x, int y, int ID);


void CreateVerticalCoridor(int y1, int y2, int x);
void CreateHorizontalCoridor(int x1, int x2, int y);

void PlaceLadderAndPlayer();

void GenerateEnemies(int roomIndex);

#endif