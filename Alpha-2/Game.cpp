#include "Game.h"
#include "Map.h"
#include "Renderer.h"
#include "Input.h"
#include "Entities.h"

#include <raylib.h>
#include <iostream>

enum RenderingMode {
	NORMAL,
	PLAYER_HEATMAP_COLOR,
	PLAYER_HEATMAP_TEXT,
};

enum RenderingMode renderingMode = NORMAL;

void GameInitialize() {
	RendererInitialize();
	MapGenerate();
}

void GameUpdate() {
	bool nextTurn = ListenToInput();
	if (nextTurn) {
		if (PlayerPositionGet().x == LadderPositionGet().x && PlayerPositionGet().y == LadderPositionGet().y)
			MapGenerate();
		EntitiesCalculateTurns();
		std::cout << "End turn" << std::endl;
	}
	if (EntitiesGet()[0]->HP == 0) {
		MapGenerate();
	}
}

void GameDraw() {
	BeginDrawing();
	ClearBackground(BLACK);

	switch (renderingMode) {
	case 0:
		MapDraw();
		EntitiesDraw();
		break;
	case 1:
		MapDraw();
		EntitiesDraw();
		HeatmapColorDraw();
		break;
	case 2:
		HeatmapTextDraw();
		break;
	}
	EndDrawing();
}


void GameClose() {
	EntitiesClear();
	RendererClose();
}