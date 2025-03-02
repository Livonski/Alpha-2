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

enum RenderingMode renderingMode = PLAYER_HEATMAP_COLOR;

void GameInitialize() {
	RendererInitialize();
	MapGenerate();
}

void GameUpdate() {
	//structure of Update
	//await for player actions
	//await for entities actions
	bool nextTurn = ListenToInput();
	if (nextTurn) {
		if (PlayerPositionGet().x == LadderPositionGet().x && PlayerPositionGet().y == LadderPositionGet().y)
			MapGenerate();
		EntitiesCalculateTurns();
		std::cout << "End turn" << std::endl;
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
	RendererClose();
}