#include <iostream>
#include <string>
#include "player.h"

player::player (board * Board, int number, int init_walls, string Player_name)
{
	path	= Board->getY ();
	y	= 0;
	x	= Board->getX ()/2 + 1;
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

// calculate a path to the end, from (a,b), as if no other players were there,
// with only the walls; it's a very primitive algorythm, but it will do for now
int
player::find_path (board * Board, int a, int b)
{
	int size_x	= Board->get_px (index),
	    size_y	= Board->get_py (index),
	    counter	= 0,
	    success	= 0,
	    direction	= 1;

	// the 2nd player has to go to the south ...
	if (index == 1)
		direction = -1;

	// we plot our walk, so we can avoid mistakes
	int ** grid = new int*[size_x];
	for (int i = 0; i <= size_x - 1; i++)
		grid [i] = new int [size_y];

	// grid is there so in case we reach the dead end, we can
	// retrace our steps, and go along a different path, than
	// the one we have already taken
	// 1 - we went up
	// 2 - we went right
	// 3 - we went left
	// 4 - we went down

	// if we're player one, we have to get to the upper side
	if (direction == 1)
	{
		do
		{
			success = 0;

			int wall_orig = Board->tile_status (a, b),
			    wall_left = Board->tile_status (a-1, b),
			    wall_down = Board->tile_status (a, b-1),
			    want      = (grid[a][b] + 1) % 5;

			if (wall_orig != 1 && wall_orig != 3 && want <= 1) 
			{
				grid [a][b] = 1;
				success = 1;
				b++;
			}

			else if (wall_orig != 2 && wall_orig != 3 && want <= 2)
			{
				grid [a][b] = 2;
				success = 1;
				a++;
			}

			else if (wall_left != 2 && wall_orig != 3 && want <= 4)
			{
				grid [a][b] = 4;
				success = 1;
				a--;
			}

			else if (wall_down != 1 && wall_orig != 3 && want <= 3)
			{
				grid [a][b] = 3;
				success = 1;
				b--;
			}

			// if no direction is good ...
			if (success == 0)
			{
				counter = 100 * size_x * size_y;
				break;
			}

			counter++;

		} while (counter <= size_x * size_y * 4 && b < size_y - 1);
	}

	// if we're player two, we have to get to the lower side
	if (direction == -1)
	{
		do
		{
			success = 0;

			int wall_orig = Board->tile_status (a, b),
			    wall_left = Board->tile_status (a-1, b),
			    wall_down = Board->tile_status (a, b-1),
			    want      = (grid[a][b] + 1) % 5;

			// first we try to go down
			if (wall_down != 1 && wall_down != 3 && want <= 3)
			{
				grid [a][b] = 3;
				success = 1;
				b--;
			}

			// then we try left
			else if (wall_left != 2 && wall_left != 3 && want <= 4)
			{
				grid [a][b] = 4;
				success = 1;
				a--;
			}

			// otherwise right
			else if (wall_orig != 2 && wall_orig != 3 && want <= 2)
			{
				grid [a][b] = 2;
				success = 1;
				a++;
			}

			// at last, we try up
			else if (wall_orig != 1 && wall_orig != 3 && want <= 1)
			{
				grid [a][b] = 1;
				success = 1;
				b++;
			}

			// if no direction is good ...
			if (success == 0)
			{
				counter = 100 * size_x * size_y;
				break;
			}

			counter++;

		} while (counter <= size_x * size_y * 4 && b > 1);
	}

	// we cleanup the mess
	for (int i = 0; i <= size_x-1; i++)
		if (grid[i]) delete [] grid[i];
	delete [] grid;

	return counter;
}

// some primitive path will do, just so we know what we're up against ;)
void
player::update_path (board * Board)
{
	path = find_path (Board, x, y);
}

void
player::update_path (int length)
{
	path = length;
}

int
player::move (board * Board, int d)
{
	// index of the other player
	int other_index = (index + 1)%2;

	int returnVal	= -1,
	    otherX	= Board->get_py (other_index),
	    otherY	= Board->get_px (other_index),
	    wallinfo;

	// we check if we can move in that direction
	// d:
	// 1 -- up
	// 2 -- right
	// 3 -- down
	// 4 -- left
	switch (d)
	{
		case 1:
			wallinfo = Board->tile_status (x, y);

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
			wallinfo = Board->tile_status (x, y);

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
			wallinfo = Board->tile_status (x, y-1);

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
			wallinfo = Board->tile_status (x-1, y);

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
			std::cout << "Error! Unknown direction.\nExiting!" << std::endl;
			exit (EXIT_FAILURE);
	}

	if (returnVal == MOVE_SUCCESS)
		update_path (sPath);

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

	int other_index = (index + 1)%2,
	    otherX	= Board->get_py (other_index),
	    otherY	= Board->get_px (other_index),
	    wall_next	= 0,
	    sPath	= 0;

	// we check if we have enough walls
	if (walls < 1)
		returnVal = PLAYER_FAYUL;

	// we check for a valid move
	switch (mode)
	{
		case 1:
			// walls cannot go out of the board
			if (xc == size_x-1)
			{
				returnVal = PLAYER_FAYUL;
				break;
			}
			wall_next = Board->tile_status (xc + 1, yc);

			// there already is a wall in the current tile
			if (wall_orig == 1 || wall_orig == 3)
				returnVal = PLAYER_FAYUL;

			// there is already a wall in the adjacent tile
			else if (wall_next == 1 || wall_next == 3)
				returnVal = PLAYER_FAYUL;

			// we check if this criples either of players
			// a) does it cripple us?
			sPath = find_path (Board, x, y);
			if (sPath >= size_x * size_y * 4)
				returnVal = PLAYER_FAYUL;

			// b) does it cripple our opponent
			sPath = find_path (Board, otherX, otherY);
			if (sPath >= size_x * size_y * 4)
				returnVal = PLAYER_FAYUL;

			// we successfully built a wall
			else if (returnVal != PLAYER_FAYUL)
			{
				Board->set_wall (xc, yc, wall_orig + mode);
				Board->set_wall (xc+1, yc, wall_next + mode);

				// but we have to check if the players can still run out

				returnVal = WALL_SUCCESS;
			}
			break;
		case 2:
			if (yc == size_y - 1)
			{
				returnVal = PLAYER_FAYUL;
				break;
			}
			wall_next = Board->tile_status (xc, yc+1);

			if (wall_orig == 2 || wall_orig == 3)
				returnVal = PLAYER_FAYUL;

			else if (wall_next == 2 || wall_next == 3)
				returnVal = PLAYER_FAYUL;

			// we check if this criples either of players
			sPath;
			// a) does it cripple us?
			sPath = find_path (Board, x, y);
			if (sPath >= size_x * size_y * 4)
				returnVal = PLAYER_FAYUL;

			// b) does it cripple our opponent
			sPath = find_path (Board, otherX, otherY);
			if (sPath >= size_x * size_y * 4)
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

	return returnVal;
}
