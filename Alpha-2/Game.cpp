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
		//When player uses ladder old player is deleted and new player is born. For now it means that player restores HP
		//But in future it could lead to various different problems
		if (PlayerPositionGet().x == LadderPositionGet().x && PlayerPositionGet().y == LadderPositionGet().y)
			MapGenerate();

		EntitiesCalculateTurns();

		if (EntitiesGet()[0]->HP == 0) {
			MapGenerate();
		}

		EntitiesOnTurnEnd();
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