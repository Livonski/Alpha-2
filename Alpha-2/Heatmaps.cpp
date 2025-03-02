#include "Heatmaps.h"
#include "Heatmap.h"

Heatmap playerMap;

void OnPlayerMove(Vector2 playerPosition) {
	playerMap.CalculateMap(playerPosition);
}

int GetPlayerHeatmapMaxDistance() {
	return playerMap.GetMaxDistance();
}

int GetPlayerHeatmapTile(int x, int y) {
	return playerMap.GetValue(x, y);
}

