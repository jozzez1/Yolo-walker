#ifndef __BOARD_GAME
#define __BOARD_GAME

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
		int get_px (int a) { return x[a]; }
		int get_py (int a) { return y[a]; }

		// checks the wall status of the tile
		int tile_status (int, int);
		
		void set_wall (int, int, int);
		void move_player (int, int, int);

		// constructor
		board (int X_dimension, int Y_dimension);

		// destructor
		~board ();
};

#endif
