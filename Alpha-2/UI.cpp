#include "UI.h"
#include "Entities.h"
#include "GlobalConsts.h"

#include "raylib.h" 

bool DrawDeathMessage = false;
int DeathMessageFontSize = 40;

void UIDraw() {
	//Health
	DrawText(TextFormat("HP: %d/%d", EntityGet(0)->HP, EntityGet(0)->maxHP), 10, GAME_HEIGHT, 20, WHITE);

	//Death message
	if (DrawDeathMessage) {
		int textWidth = MeasureText("You are DEAD", DeathMessageFontSize);
		int textPosX = GAME_WIDTH / 2 - textWidth / 2;
		int textPosY = GAME_HEIGHT / 2 - DeathMessageFontSize / 2;

		DrawRectangle(textPosX, textPosY, textWidth, DeathMessageFontSize, BLACK);
		DrawText(TextFormat("You are DEAD"), textPosX, textPosY, DeathMessageFontSize, RED);
	}

	//FPS
	DrawFPS(GAME_WIDTH - 100, GAME_HEIGHT);
}

void ShouldDrawDeathMessage(bool dead) {
	DrawDeathMessage = dead;
}