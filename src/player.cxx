#include <iostream>
#include <string>
#include "player.h"

void
player::player (board * Board, int number, int init_walls, string Player_name)
{
	path	= Board->getY ();
	y	= 0;
	x	= Board->getX () /2;
	walls	= init_walls;

	// we have to give him the index
	index	= number;

	// and the name
	name.assign (Player_name);

	// first player starts
	if (index == 0)
		turn_info = 1;

	// 2nd player has to wait
	else
		turn_info = 0;
}

int
player::move (board * Board, int d)
{
	// index of the other player
	int other_index = (index + 1)%2;

	int returnVal	= -1,
	    otherX	= Board->get_py (other_index),
	    otherY	= Board->get_px (other_index);

	// we check if we can move in that direction
	// d:
	// 1 -- up
	// 2 -- right
	// 3 -- down
	// 4 -- left
	switch (d)
	{
		case 1:
			int wallinfo = Board->tile_status (x, y);

			// they cannot walk through the walls
			if (wallinfo == 1 || wallinfo == 3)
				returnVal = PLAYER_FAYUL;

			// they cannot be on the same spot hehehe
			else if (x == otherX && y+1 == otherY)
				returnVal = PLAYER_FAYUL;

			// the move is a success
			else
			{
				y++;
				Board->move_player (index, x, y+1);
				returnVal = MOVE_SUCCESS;
			}
			break;
		case 2:
			int wallinfo = Board->tile_status (x, y);

			// again check for walls
			if (wallinfo == 2 || wallinfo == 3)
				returnVal = PLAYER_FAYUL;

			// again, they cannot move in the same spot
			else if (y == otherY && x+1 == otherX)
				returnVal = PLAYER_FAYUL;

			// a successful move
			else
			{
				x++;
				Board->move_player (index, x+1, y);
				returnVal = MOVE_SUCCESS;
			}
			break;
		case 3:
			int wallinfo = Board->tile_status (x, y-1);

			if (wallinfo == 1 || wallinfo == 3)
				returnVal = PLAYER_FAYUL;

			else if (x == otherX && y-1 == otherY)
				returnVal = PLAYER_FAYUL;

			else
			{
				y--;
				Board->move_player (index, x, y-1);
				returnVal = MOVE_SUCCESS;
			}
			break;
		case 4:
			int wallinfo = Board->tile_status (x-1, y);

			if (wallinfo == 2 || wallinfo == 3)
				returnVal = PLAYER_FAYUL;

			if (y == otherY && x-1 == otherX)
				returnVal = PLAYER_FAYUL;

			else
			{
				x--;
				Board->move_player (index, x-1, y);
				returnVal = MOVE_SUCCESS;
			}
			break;
		default:
			std::cout << "Error! Unknown direction.\nExiting!" << std:endl;
			exit (EXIT_FAILURE);
	}

	if (returnVal == MOVE_SUCCESS)
		player::update_path (Board);

	return returnVal;
}

int
player::wall (board * Board, int xc, int yc, int mode)
{
	// walls have size '2' so we have to check for one more side left

	int wall_orig 	= Board->tile_status (xc, yc),
	    size_x	= Board->getX (),
	    size_y	= Board->getY (),
	    returnVal	= -1;

	// we check if we have enough walls
	if (walls < 1)
		returnVal = WALLS_FAYUL;

	// we check for a valid move
	switch (mode)
	{
		case 1:
			// walls cannot go out of the board
			if (xc == size_x-1)
				returnVal = PLAYER_FAYUL;

			// there already is a wall in the current tile
			else if (wall_orig == 1 || wall_orig == 3)
				returnVal = PLAYER_FAYUL;

			// there is already a wall in the adjacent tile
			int wall_next = Board->tile_status (xc + 1, yc);
			else if (wall_next == 1 || wall_next == 3)
				returnVal = PLAYER_FAYUL;

			// we successfully built a wall
			else
			{
				Board->set_wall (xc, yc, wall_orig + mode);
				Board->set_wall (xc+1, yc, wall_next + mode);

				returnVal = WALL_SUCCESS;
			}
			break;
		case 2:
			if (yc == size_y - 1)
				returnVal = PLAYER_FAYUL;

			else if (wall_orig == 2 || wall_orig == 3)
				returnVal = PLAYER_FAYUL;

			int wall_next = Board_>tile_status (xc, yc + 1);
			else if (wall_next == 2 || wall_next == 3)
				returnVal = PLAYER_FAYUL;

			else
			{
				Board->set_wall (xc, yc, wall_orig + mode);
				Board->set_wall (xc, yc + 1, wall_next + mode);

				returnVal = WALL_SUCCESS;
			}
			break;
		default:
			std::cout << "Error! Unknown wall specification!\nExiting." << std::endl;
			exit (EXIT_FAILURE);
	}
}
