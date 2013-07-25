#ifndef __PLAYER
#define __PLAYER

#define MOVE_SUCCESS	15
#define WALL_SUCCESS	14
#define PLAYER_FAYUL	13

#include "board.h"

using namespace std;

// the player class
class player
{
	private:
		int path,	// shortest path to the finish
		    index,	// player 1,2, ... , n
		    walls;	// number of walls a player can still build

		int turn_info;	// if the turn is successfull or not

		string name;	// player's name
		
		void update_path (board *);

	public:
		int x,		// x position on the board
		    y;		// y position on the board

		// some self-explainatory functions
		int get_path ()	{ return path; }
		int get_walls() { return walls; }

		void set_walls (int);

		int move (board *, int, int);
		int wall (board *, int, int, int);
		int find_path (board *, int, int);
		int move (board *, int);

		// set starting x-coordinate
		// int setX ();

		// constructor
		player (board *, int, int, string);

		// destructor
		~player ();
};

#endif
