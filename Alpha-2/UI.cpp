#include "UI.h"
#include "Entities.h"
#include "GlobalConsts.h"

#include "raylib.h" 

void UIDraw() {
	DrawText(TextFormat("HP: %d/%d", EntitiesGet()[0]->HP, EntitiesGet()[0]->maxHP), 10, GAME_HEIGHT, 20, WHITE);
}