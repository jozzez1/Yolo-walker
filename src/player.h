#ifndef __PLAYER
#define __PLAYER

#define MOVE_SUCCESS 15
#define WALL_SUCCESS 14

// the player class
class player
{
	private:
		int path,	// shortest path to the finish
		    index;	// player 1,2, ... , n

		string player_name;
		
		void update_path (board);

	public:
		int x,		// x position on the board
		    y;		// y position on the board

		// some self-explainatory functions
		int get_path ()	{ return path; }
		int move (board);
		int wall (board);

		// set starting x-coordinate
		// int setX ();

		// constructor
		void player (board);

		// destructor
		void ~player ();
}

#endif
