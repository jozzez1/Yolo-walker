#include "board.h"

board::board (int X_dimension, int Y_dimension)
{
	X 	= X_dimension;
	Y	= Y_dimension;

	// we set them just to initialize them, although it's unnecessary
	x[0]	= 0;
	x[1]	= 0;
	y[0]	= 0;
	y[1]	= Y;
}

