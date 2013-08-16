#include "player.hpp"

player::player (int number,		// player index -- 0 = player 1, 1 = player2
		int init_x,		// starting x
		int init_y,		// starting y
		int init_walls,		// starting number of walls
		string Player_name)	// player name
{
	x	= init_x;
	y	= init_y;
	walls	= init_walls;

	// we have to give him the index
	index	= number;

	// and the name
	name.assign (Player_name);
}

player::~player ()
{

}

// we move the player to a different location
void
player::move (int x_new, int y_new)
{
	x = x_new;
	y = y_new;
}

/* WORK IN PROGRESS
// we use the keyboard/mouse to get the input
// see SDL manual on how to do that
trn
player::get_input ()
{

}
*/
