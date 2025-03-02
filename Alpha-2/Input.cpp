#include "Input.h"
#include "Entities.h"

#include "raylib.h"
#include <iostream>

bool ListenToInput() {
	Vector2 playerMovementDirection = { 0, 0 };
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_KP_8))
		playerMovementDirection = { 0, -1 };
	if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_KP_2))
		playerMovementDirection = { 0, 1 };
	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_KP_4))
		playerMovementDirection = { -1, 0 };
	if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_KP_6))
		playerMovementDirection = { 1, 0 };

	if (IsKeyPressed(KEY_KP_7))
		playerMovementDirection = { -1, -1 };
	if (IsKeyPressed(KEY_KP_9))
		playerMovementDirection = { 1 , -1 };
	if (IsKeyPressed(KEY_KP_1))
		playerMovementDirection = { -1, 1 };
	if (IsKeyPressed(KEY_KP_3))
		playerMovementDirection = { 1 , 1 };

	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_R))
		PlayerPositionSet(LadderPositionGet().x, LadderPositionGet().y);
	
	PlayerMove(playerMovementDirection);

	return (GetKeyPressed() != KEY_NULL);
}