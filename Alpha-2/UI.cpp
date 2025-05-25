#include "UI.h"
#include "Entities.h"
#include "GlobalConsts.h"

#include "raylib.h" 

bool DrawDeathMessage = false;
int DeathMessageFontSize = 40;

int UIBarWidth;

void UIDraw() {
	UIBarWidth = 0;

	//Health
	DrawText(TextFormat("HP: %d/%d", EntityGet(0)->HP, EntityGet(0)->maxHP), 10, GAME_HEIGHT, 20, WHITE);
	UIBarWidth += 10 + MeasureText(TextFormat("HP: %d/%d", EntityGet(0)->HP, EntityGet(0)->maxHP), 20);

	//Damage
	DrawText(TextFormat("Damage: %d", EntityGet(0)->damage), UIBarWidth + 10, GAME_HEIGHT, 20, WHITE);
	UIBarWidth += 10 + MeasureText(TextFormat("Damage: %d", EntityGet(0)->damage), 20);

	//XP & Level
	DrawText(TextFormat("Level: %d", EntityGet(0)->Level), UIBarWidth + 10, GAME_HEIGHT, 20, WHITE);
	UIBarWidth += 10 + MeasureText(TextFormat("Level: %d", EntityGet(0)->Level), 20);

	DrawText(TextFormat("XP: %d/%d", EntityGet(0)->XP, EntityGet(0)->maxXP), UIBarWidth + 10, GAME_HEIGHT, 20, WHITE);
	UIBarWidth += 10 + MeasureText(TextFormat("HP: %d/%d", EntityGet(0)->XP, EntityGet(0)->maxXP), 20);

	//Death message
	if (DrawDeathMessage) {
		int textWidth = MeasureText("You are DEAD", DeathMessageFontSize);
		int textPosX = GAME_WIDTH / 2 - textWidth / 2;
		int textPosY = GAME_HEIGHT / 2 - DeathMessageFontSize / 2;

		DrawRectangle(textPosX, textPosY, textWidth, DeathMessageFontSize, BLACK);
		DrawText(TextFormat("You are DEAD"), textPosX, textPosY, DeathMessageFontSize, RED);
	}

	//FPS
	DrawFPS(UIBarWidth + 10, GAME_HEIGHT);
}

void ShouldDrawDeathMessage(bool dead) {
	DrawDeathMessage = dead;
}