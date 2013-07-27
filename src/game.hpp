// a general header file with some structs and some other
// things, like signal definitions for successful moves and
// so on

#ifndef __GAME_YOLO_WALKER
#define __GAME_YOLO_WALKER

// player did a valid move: move or wall
#define ALL_CLEAR	16

// the move is valid
#define MOVE_SUCCESS	15

// walls are placed in a valid way
#define WALL_SUCCESS	14

// player attempted an invalid move
#define PLAYER_FAYUL	13

// struct with output from a player turn
typedef struct trn
{
	int wall;	// if we built a wall or not
			// 0 - no wall
			// 1 - wall mode 1
			// 2 - wall mode 2
			// 3 - wall mode 3

	int x,		// x-coordinate for wall/movement
	    y;		// y-coordinate for wall/movement
} trn;

#endif
