#include "Game.h"
#include "Map.h"
#include "Renderer.h"
#include "Input.h"
#include "Entities.h"
#include "UI.h"

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


		EntitiesOnTurnEnd();
		std::cout << "End turn" << std::endl;
	}
	if (EntityGet(0)->HP <= 0) {
		EntitiesClear();
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
		UIDraw();
		break;
	case 1:
		MapDraw();
		EntitiesDraw();
		UIDraw();
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