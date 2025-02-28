#include "Map.h"
#include "Entities.h"
#include "GlobalConsts.h"

#include <iostream>

const int ROOMS_NUM = 5;
const int ROOM_MIN_SIZE = 5;
const int ROOM_MAX_SIZE = 10;

int map[WORLD_WIDTH][WORLD_HEIGHT];

struct Room {
	int X{};
	int Y{};
	int Width{};
	int Height{};
	int CenterX = (int) X + Width / 2;
	int CenterY = (int) Y + Height / 2;
	int ConnectionsNum{};
};

Room rooms[ROOMS_NUM]{};

static bool Intersects(Room r1, Room r2) {
	return !(r1.X + r1.Width < r2.X  ||
			 r1.X > r2.X + r2.Width  ||
			 r1.Y + r1.Height < r2.Y ||
			 r1.Y > r2.Y + r2.Height);
}

void MapGenerate() {
	std::cout << "Generating map" << std::endl;
	EntitiesClear();
	std::cout << WORLD_HEIGHT << " " << WORLD_WIDTH << std::endl;
	srand(time(0));

	//std::fill(map, map + WORLD_WIDTH * WORLD_HEIGHT, -1);
	for (int y = 0; y < WORLD_HEIGHT; y++) {
		for (int x = 0; x < WORLD_WIDTH; x++) {
			map[x][y] = TILE_INDEX_WALL;
		}
	}

	for (int i = 0; i < ROOMS_NUM; i++) {
		bool succes = false;
		while (!succes) {
			if (i == 0)
				succes = true;
			Room roomNew{};
			roomNew.Width   = rand() % ROOM_MAX_SIZE + ROOM_MIN_SIZE;
			roomNew.Height  = rand() % ROOM_MAX_SIZE + ROOM_MIN_SIZE;
			roomNew.X       = rand() % (WORLD_WIDTH  - roomNew.Width  - 1) + 1;
			roomNew.Y       = rand() % (WORLD_HEIGHT - roomNew.Height - 2) + 1;
			roomNew.CenterX = (int)roomNew.X + roomNew.Width  / 2;
			roomNew.CenterY = (int)roomNew.Y + roomNew.Height / 2;

			for (int j = 0; j < i; j++) {
				Room room = rooms[j];
				if (Intersects(roomNew, room)) {
					succes = false;
					break;
				}
				succes = true;
			}
			rooms[i] = roomNew;
		}

		for (int y = rooms[i].Y; y < rooms[i].Y + rooms[i].Height; y++) {
			for (int x = rooms[i].X; x < rooms[i].X + rooms[i].Width; x++) {
				map[x][y] = TILE_INDEX_FLOOR;
			}
		}

		GenerateEnemies(i);

		//std::cout << "Size: " << rooms[i].Width << ":" << rooms[i].Height << ", Center: " << rooms[i].CenterX << ":" << rooms[i].CenterY << std::endl;
	}

	for (int i = 0; i < ROOMS_NUM; i++) {
		Room roomMain = rooms[i];
		Room roomToConnect;
		int minConnections = -1;
		for (int j = 0; j < ROOMS_NUM; j++) {
			if (i == j)
				continue;
			if (rooms[j].ConnectionsNum > minConnections) {
				minConnections = rooms[j].ConnectionsNum;
				roomToConnect = rooms[j];
			}
		}

		//std::cout << "Center X: " << roomToConnect.CenterX << ":" << roomMain.CenterX << ", CenterY: " << roomToConnect.CenterY << ":" << roomMain.CenterY << ",d : " << dX << ":" << dY << std::endl;

		if ((rand() % 100) > 50) {
			CreateHorizontalCoridor(roomMain.CenterX, roomToConnect.CenterX, roomMain.CenterY);
			CreateVerticalCoridor(roomMain.CenterY, roomToConnect.CenterY, roomToConnect.CenterX);
		 }
		else {
			CreateVerticalCoridor(roomMain.CenterY, roomToConnect.CenterY, roomMain.CenterX);
			CreateHorizontalCoridor(roomMain.CenterX, roomToConnect.CenterX, roomToConnect.CenterY);
		}

		roomMain.ConnectionsNum++;
		roomToConnect.ConnectionsNum++;
	}

	PlaceLadderAndPlayer();
}

int GetTile(int x, int y) {
	if (x < 0 || x > WORLD_WIDTH || y < 0 || y > WORLD_HEIGHT)
		throw std::runtime_error("Map, GetTile, trying to get tile outside of map bounds");
	return map[x][y];
}

bool IsMovable(int x, int y) {
	if (x < 0 || x > WORLD_WIDTH || y < 0 || y > WORLD_HEIGHT)
		throw std::runtime_error("Map, IsMovable, trying to get tile outside of map bounds");
	return map[x][y] != TILE_INDEX_WALL;
}

void CreateVerticalCoridor(int y1, int y2, int x) {
	for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
		if (x > 0 && x < WORLD_WIDTH && y > 0 && y < WORLD_HEIGHT)
			map[x][y] = TILE_INDEX_FLOOR;
	}
}

void CreateHorizontalCoridor(int x1, int x2, int y) {
	for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
		if (x > 0 && x < WORLD_WIDTH && y > 0 && y < WORLD_HEIGHT)
			map[x][y] = TILE_INDEX_FLOOR;
	}
}

void PlaceLadderAndPlayer() {
	int ladderRoomIndex = rand() % ROOMS_NUM;
	int playerRoomIndex = (ladderRoomIndex + 1) % ROOMS_NUM;
	std::cout << ladderRoomIndex << " : " << playerRoomIndex << std::endl;

	LadderPositionSet(rooms[ladderRoomIndex].CenterX, rooms[ladderRoomIndex].CenterY);
	map[rooms[ladderRoomIndex].CenterX][rooms[ladderRoomIndex].CenterY] = TILE_INDEX_LADDER;

	PlayerPositionSet(rooms[playerRoomIndex].CenterX, rooms[playerRoomIndex].CenterY);
}

void GenerateEnemies(int roomIndex) {
	Room room = rooms[roomIndex];
	int enemiesNum = rand() % ENEMIES_NUM_MAX + ENEMIES_NUM_MIN;

	int minX = room.X + 1;
	int maxX = room.X + room.Width - 1;
	int minY = room.Y + 1;
	int maxY = room.Y + room.Width - 1;

	std::cout << "X: " << minX << " : " << maxX << ", Y:" << minY << " : " << maxY << std::endl;

	for (int j = 0; j < enemiesNum; j++) {
		Vector2 randomPosition = { rand() % (maxX - minX + 1) + minX, rand() % (maxY - minY + 1) + minY };
		
		//For some reason sometimes enemies spawn outside of room bounds;
		if (map[(int)randomPosition.x][(int)randomPosition.y] != TILE_INDEX_FLOOR)
			continue;


		AddEntity(randomPosition, TILE_INDEX_L_G, GREEN);
	}
}