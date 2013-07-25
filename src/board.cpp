#include "board.h"

board::board (int X_dimension, int Y_dimension)
{
	X 	= X_dimension;
	Y	= Y_dimension;

	// we set them just to initialize them, although it's unnecessary
	x = new int [2];
	y = new int [2];

	x[0]	= 0;
	x[1]	= 0;
	y[0]	= 0;
	y[1]	= Y;

	// we initialize with an empty board -- all elements are zero
	M = new int*[X];
	for (int i = 0; i <= X-1; i++)
		M[i] = new int [Y];
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
	return M [xc][yc];
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

board::~board ()
{
	for (int i = 0; i <= X-1; i++)
		delete [] M[i];

	delete [] M;
	delete [] x;
	delete [] y;
}

