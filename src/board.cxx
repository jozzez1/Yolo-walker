#include "board.h"

void
board::board (int X_dimension, int Y_dimension)
{
	X 	= X_dimension;
	Y	= Y_dimension;

	// we set them just to initialize them, although it's unnecessary
	x[0]	= 0;
	x[1]	= 0;
	y[0]	= 0;
	y[1]	= Y;

	// we initialize with an empty board -- all elements are zero
	M = (int **) malloc (X * sizeof (int *));
	for (int i = 0; i <= X-1; i++)
		M[i] = (int *) calloc (Y, sizeof (int));

	// wall codes, for further reference
	/////////////////////////////////////////////
	// 0 -- nothing on this tile
	// 1 -- wall on the upper side
	// 2 -- wall on the right side
	// 3 -- wall on the upper and the right side
}

int
board::tile_status (int x, int y)
{

}

// this function checks if the board is consistent with the game rules
void
board::check_board ()
{
	
}
