#ifndef __BOARD_GAME
#define __BOARD_GAME

#define BOARD_ALL_CLEAR	13
#define PLAYER_FAIL	12
#define WALLS_FAYUL	11

class board
{
	private:
		int * x, // array with x-coordinates of players
		    * y; // array with y-coordinates of players

		int ** M;// the actual board -- info about walls and such

		int X,   // dimension of the board in X
		    Y;   // dimension of the board in Y
	
	public:
		int getX () { return X; }
		int getY () { return Y; }

		// get player1/2 coordinates
		int get_p1x () { return x[0]; }
		int get_p1y () { return y[0]; }
		int get_p2x () { return x[1]; }
		int get_p2y () { return y[0]; }

		// check if everything is ok:
		// walls don't overlap each other, there are ways out
		// players are on different positions
		int check_board ();

		// checks the wall status of the tile
		int tile_status (int, int);

		// constructor
		void board (int, int);
}

#endif
