#ifndef MAP_H
#define MAP_H

void MapGenerate();

int GetTile(int x, int y);
bool IsMovable(int x, int y);

void CreateVerticalCoridor(int y1, int y2, int x);
void CreateHorizontalCoridor(int x1, int x2, int y);

void PlaceLadderAndPlayer();

void GenerateEnemies(int roomIndex);

#endif