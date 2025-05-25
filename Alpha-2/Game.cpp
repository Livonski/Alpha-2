#include "Game.h"
#include "Map.h"
#include "Renderer.h"
#include "Input.h"
#include "Entities.h"
#include "UI.h"

#include <raylib.h>
#include <iostream>

/* Possible game states
*   -Initializing game:
*	--Initialize renderer
* 
*	-Creating new game session:
*	--Initialize entities?
*	--Generate map	
* 
*	-Generating new level:
*	--Clear entities
*	--Generate map
* 
*   -Player death screen:
*	--Wait for input
* 
*   -Updating game:
*	--Wait for input
*	--Process stuff
*/



enum RenderingMode {
	NORMAL,
	PLAYER_HEATMAP_COLOR,
	PLAYER_HEATMAP_TEXT,
};

enum GameState {
	INITIALIZING,
	CREATING_NEW_GAME_SESSION,
	CREATING_NEW_LEVEL,
	SHOWING_DEATH_SCREEN,
	UPDATING_GAME
};

enum RenderingMode renderingMode = NORMAL;
enum GameState state = INITIALIZING;


void GameInitialize() {
	RendererInitialize();
	MapGenerate();
}

void GameStartNew() {
	EntitiesClear();
	MapGenerate();
}

void LevelGenerateNew() {
	EntitiesLevelClear();
}

void GameUpdate() {
	bool recievedInput = false;

	switch (state) {
	case INITIALIZING:
		GameInitialize();
		state = UPDATING_GAME;
		break;

	case CREATING_NEW_GAME_SESSION:
		GameStartNew();
		state = UPDATING_GAME;
		break;

	case CREATING_NEW_LEVEL:
		break;

	case SHOWING_DEATH_SCREEN:
		ShouldDrawDeathMessage(true);
		recievedInput = ListenToInput();
		if (recievedInput) {
			ShouldDrawDeathMessage(false);
			state = CREATING_NEW_GAME_SESSION;
		}
		break;

	case UPDATING_GAME:
		recievedInput = ListenToInput();
		if (recievedInput) {
			if (PlayerPositionGet().x == LadderPositionGet().x && PlayerPositionGet().y == LadderPositionGet().y)
				MapGenerate();

			EntitiesCalculateTurns();

			EntitiesOnTurnEnd();
			std::cout << "End turn" << std::endl;
		}
		if (EntityGet(0)->HP <= 0) {
			state = SHOWING_DEATH_SCREEN;
		}
		break;
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