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
board::tile_status (int xc, int yc)
{
	return M[x][y];
}

void
board::move_player (int index, int xc, int yc)
{
	x[index] = xc;
	y[index] = yc;

	// followed by some draw function we'll add later
}

void
board::set_wall (int xc, int yc, int mode)
{
	M[xc][yc] = mode;

	// followed by some draw function we'll add later
}

void
board::~board ()
{
	for (int i = 0; i <= X-1; i++)
		free (M[i]);
	free (M);

	free (x);
	free (y);
}

