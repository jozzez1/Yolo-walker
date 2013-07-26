#include "engine.h"

engine::engine (int init_walls,
		string p1_name,
		string p2_name,
		int X-dim,
		int Y-dim)
{
	Board	= new board (X-dim, Y-dim);
	p	= new player * [2];
	p[0]	= new player (Board, 0, init_walls, p1_name);
	p[1]	= new player (Board, 1, init_walls, p2_name);
	
	turn	= 0;
}

engine::~engine ()
{
	delete [] p[1];
	delete [] p[0];
	delete [] p;
	delete board;
}

int
engine::give_turn ()
{

}
