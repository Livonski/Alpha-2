#include "Renderer.h"
#include "Map.h"
#include "Entities.h"
#include "GlobalConsts.h"
#include "Heatmaps.h"

#include <raylib.h>
#include <iostream>
#include <vector>

Texture2D tileset;

void RendererInitialize() {
	std::cout << "Initializing renderer" << std::endl;
	tileset = LoadTexture("Assets/16x16_sm_ascii.png");
}


void MapDraw() {
	//std::cout << "Drawing map" << std::endl;
	for (int y = 0; y < WORLD_HEIGHT; y++) {
		for (int x = 0; x < WORLD_WIDTH; x++) {
			int tile = GetTileTilesetIndex(x, y);
			Rectangle tileRect = { (tile % TILESET_WIDTH) * TILE_SIZE, (int)(tile / TILESET_HEIGHT) * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			Vector2 tilePos = { x * TILE_SIZE, y * TILE_SIZE };
			DrawTextureRec(tileset, tileRect, tilePos, DARKGRAY);
		}
	}
}

void EntitiesDraw() {
	//std::cout << "Drawing entities" << std::endl;
	Rectangle tileRect = { (TILE_INDEX_PLAYER % TILESET_WIDTH) * TILE_SIZE, (int)(TILE_INDEX_PLAYER / TILESET_HEIGHT) * TILE_SIZE, TILE_SIZE, TILE_SIZE };
	Vector2 playerPos = PlayerPositionGet();
	playerPos.x *= TILE_SIZE;
	playerPos.y *= TILE_SIZE;
	DrawTextureRec(tileset, tileRect, playerPos, WHITE);

	std::vector<Entity> entities = EntitiesGet();
	for (int i = 0; i < entities.size(); i++) {
		Rectangle tileRect = { (entities[i].tileIndex % TILESET_WIDTH) * TILE_SIZE, (int)(entities[i].tileIndex / TILESET_HEIGHT) * TILE_SIZE, TILE_SIZE, TILE_SIZE};
		Vector2 entityPos = entities[i].position;
		entityPos.x *= TILE_SIZE;
		entityPos.y *= TILE_SIZE;
		DrawTextureRec(tileset, tileRect, entityPos, entities[i].color);
	}
}

void HeatmapColorDraw() {
	int maxDistance = GetPlayerHeatmapMaxDistance();
	for (int y = 0; y < WORLD_HEIGHT; y++) {
		for (int x = 0; x < WORLD_WIDTH; x++) {
			int distance = GetPlayerHeatmapTile(x, y);
			float ratio  = 1 - (float)distance / (float)maxDistance;
			if (distance == -1)
				ratio = 0;
			//std::cout << "ratio: " << ratio << ", distance: " << distance << ", maxDistance: " << maxDistance << std::endl;
			Color color = { ratio * 256, ratio * 256, ratio * 256, 0.5 * 256 };
			DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
		}
	}
}

void HeatmapTextDraw() {
	// Проходим по каждой ячейке массива
	for (int y = 0; y < WORLD_HEIGHT; y++) {
		for (int x = 0; x < WORLD_WIDTH; x++) {
			int value = GetPlayerHeatmapTile(x, y);

			// Выбираем цвет текста в зависимости от значения
			Color textColor = WHITE;
			if (value == -1) {
				textColor = RED;
			}
			else if (value > 0) {
				textColor = GREEN;
			}

			// Вычисляем позицию ячейки на экране
			int posX = x * TILE_SIZE;
			int posY = y * TILE_SIZE;

			// Отрисовываем фон ячейки (например, черный) и рамку (серый)
			DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, BLACK);
			DrawRectangleLines(posX, posY, TILE_SIZE, TILE_SIZE, DARKGRAY);

			// Форматируем значение ячейки в строку
			const char* text = TextFormat("%d", value);
			int fontSize = 10;  // Размер шрифта (можно изменить)
			int textWidth = MeasureText(text, fontSize);

			// Центрируем текст в ячейке
			int textX = posX + (TILE_SIZE - textWidth) / 2;
			int textY = posY + (TILE_SIZE - fontSize) / 2;
			DrawText(text, textX, textY, fontSize, textColor);
		}
	}
}

void RendererClose() {
	std::cout << "Closing renderer" << std::endl;
	UnloadTexture(tileset);
}