#include "Heatmap.h"
#include "Map.h"
#include "GlobalConsts.h"

#include "raylib.h"
#include <iostream>
#include <stack>
#include <queue>


int heatMap[WORLD_WIDTH][WORLD_HEIGHT];
int maxDistance = 0;

void Heatmap::CalculateMap(Vector2 playerPosition) {
	memset(heatMap, 0, sizeof(heatMap));

	std::queue<Vector2> q;
	//Vector2 origin = playerPosition;
	q.push(playerPosition);
	
	//int currentDistance = 1;
	heatMap[(int)playerPosition.x][(int)playerPosition.y] = 1;



	while (!q.empty()) {
		Vector2 origin = q.front();
		q.pop();
		int currentDistance = heatMap[(int)origin.x][(int)origin.y];
		maxDistance = std::max(currentDistance, maxDistance);

		for (int y = origin.y - 1; y <= origin.y + 1; y++) {
			for (int x = origin.x - 1; x <= origin.x + 1; x++) {
				if (x < 0 || y < 0 || x >= WORLD_WIDTH || y >= WORLD_HEIGHT)
					continue;
				if (heatMap[x][y] != 0)
					continue;
				if (!IsWalkable(x, y)) {
					heatMap[x][y] = -1;
					continue;
				}

				heatMap[x][y] = currentDistance + 1;
				Vector2 target{ x, y };
				q.push(target);
			}
		}
	}
}

int Heatmap::GetValue(int x, int y) {
	return heatMap[x][y];
}

int Heatmap::GetMaxDistance() {
	return maxDistance;
}