#ifndef HEATMAP_H
#define HEATMAP_H

#include "raylib.h"

class Heatmap {
public:
	void CalculateMap(Vector2 playerPosition);
	int GetValue(int x, int y);
	int GetMaxDistance();
};

#endif
