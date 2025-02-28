#include "Game.h"
#include "Map.h"
#include "Renderer.h"
#include "Input.h"
#include "Entities.h"

#include <raylib.h>
//#include <iostream>

void GameInitialize() {
	RendererInitialize();
	MapGenerate();
}

void GameUpdate() {
	//structure of Update
	//await for entities actions
	//await for player actions
	ListenToInput();
	if (PlayerPositionGet().x == LadderPositionGet().x && PlayerPositionGet().y == LadderPositionGet().y)
		MapGenerate();
}

void GameDraw() {
	BeginDrawing();
	ClearBackground(BLACK);

	MapDraw();
	EntitiesDraw();

	EndDrawing();
}


void GameClose() {
	RendererClose();
}