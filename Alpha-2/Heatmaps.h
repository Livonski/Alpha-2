#ifndef HEATMAPS_H
#define HEATMAPS_H

#include "raylib.h"

void OnPlayerMove(Vector2 playerPosition);
int GetPlayerHeatmapMaxDistance();
int GetPlayerHeatmapTile(int x, int y);

#endif
