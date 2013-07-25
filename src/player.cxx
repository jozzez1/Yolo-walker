#include "player.h"

void
player::player (board Board)
{
	path	= Board->getY ();
	y	= 0;
	x	= Board->getX () /2;
}

