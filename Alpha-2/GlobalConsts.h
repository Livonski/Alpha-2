#ifndef GLOBALCONSTS_H
#define GLOBALCONSTS_H

const int WORLD_SEED = 42069;

//Tile stuff
	
	//Path and stuff	
	
	//const char* TILESET_PATH   = "acsii";
	const int TILE_SIZE      = 16;
	const int TILESET_HEIGHT = 16;
	const int TILESET_WIDTH  = 16;

	//Tile indexes

	const int TILE_INDEX_WALL     = 35;
	const int TILE_INDEX_FLOOR    = 46;
	const int TILE_INDEX_LADDER   = 31;
	const int TILE_INDEX_PLAYER   = 64;
	const int TILE_INDEX_L_G      = 103;


//Window stuff

	const int UI_HEIGHT = 20;
	const int UI_WIDTH  = 800;
	const int GAME_HEIGHT = 608;
	const int GAME_WIDTH = 800;


	const int WINDOW_HEIGHT = GAME_HEIGHT + UI_HEIGHT;
	const int WINDOW_WIDTH = GAME_WIDTH;

	const int WORLD_WIDTH  = GAME_WIDTH  / TILE_SIZE;
	const int WORLD_HEIGHT = GAME_HEIGHT / TILE_SIZE;

//Entities stuff
	const int ENEMIES_NUM_MIN = 1;
	const int ENEMIES_NUM_MAX = 2;
#endif