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

	const int WINDOW_HEIGHT = 608;
	const int WINDOW_WIDTH  = 800;

	const int WORLD_WIDTH = WINDOW_WIDTH / TILE_SIZE;
	const int WORLD_HEIGHT = WINDOW_HEIGHT / TILE_SIZE;

//Entities stuff
	const int ENEMIES_NUM_MIN = 2;
	const int ENEMIES_NUM_MAX = 5;
#endif