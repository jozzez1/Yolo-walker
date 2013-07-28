#include "engine.hpp"

// constructor
engine::engine (int init_walls,
		string p1_name,
		string p2_name,
		int Xdim,
		int Ydim)
{
	Board	= new board (Xdim, Ydim);
	p	= new player * [2];
	p[0]	= new player (0, Xdim/2+1, 0, init_walls, p1_name);
	p[1]	= new player (1, Xdim/2+1, Ydim, init_walls, p2_name);
	
	turn	= 0;
}

// destrurctor
engine::~engine ()
{
	delete p[1];
	delete p[0];
	delete [] p;
	delete Board;
}

// we give a turn to the player, until it is
// successfull (see, valid)
trn
engine::give_turn ()
{
	int status;

	trn player_wants;

	do
	{
		player_wants = p[turn % 2]->get_input ();
		status = check_turn (player_wants);
	} while (status != ALL_CLEAR);

	return player_wants;
}

// we give the turn to the player, and then
// make the proper changes in the board
int
engine::make_turn ()
{
	trn player_turn = give_turn ();

	if (!player_turn.wall)
	{
		p [turn % 2]->move (player_turn.x, player_turn.y);
		Board->move (turn % 2, player_turn.x, player_turn.y);
	}

	else if (player_turn.wall == 1 || player_turn.wall == 2)
	{
		// we lose one wall
		p [turn % 2]->use_wall ();

		// we set the wall on the 1st tile
		Board->set_wall (player_turn.x, player_turn.y, player_turn.wall);
		
		// and the wall on the 2nd tile
		if (player_turn.wall == 1)
			Board->set_wall (player_turn.x + 1, player_turn.y, player_turn.wall);

		else if (player_turn.wall == 2)
			Board->set_wall (player_turn.x, player_turn.y + 1, player_turn.wall);

		// error if something fishy goes on
		else
			std::cout << "Yaba daba doo-doo! It seems you have an error ...!" << std::endl;
	}

	turn++;
	return check_victory ();
}

// we check for validity of player's move
int
engine::check_turn (trn player_wants)
{
	int turn_signal;

	if (!player_wants.wall)
		turn_signal = check_move (player_wants);

	else if (player_wants.wall == 1 || player_wants.wall == 2)
		turn_signal = check_wall (player_wants);

	else
	{
		std::cout << "Darn, there has been an error with the player's input.\nCiao!" << std::endl;
		exit (EXIT_FAILURE);
	}

	if (turn_signal == MOVE_SUCCESS || turn_signal == WALL_SUCCESS)
		turn_signal = ALL_CLEAR;

	return turn_signal;
}

int
engine::check_move (trn player_want)
{
	// index of the other player
	int other_index = (turn + 1)%2;

	int returnVal	= -1,
	    otherX	= Board->get_py (other_index),
	    otherY	= Board->get_px (other_index),
	    playerX	= Board->get_py (turn%2),
	    playerY	= Board->get_px (turn%2),
	    wallinfo;

	// we check if the wanted destination is indeed
	// close enough -- 1st norm of the difference vector
	// must be one
	int dist = abs (player_want.x - playerX) +
		abs (player_want.y - playerY);

	if (dist != 1)
		returnVal = PLAYER_FAYUL;

	if (returnVal != PLAYER_FAYUL)
	{
		int d = 0;
		// we now check for direction -- d
		// d:
		// 1 -- up
		// 2 -- right
		// 3 -- down
		// 4 -- left
		// we will need it for keyboard input,
		// which will only give us direction
		if (!d)
		{
			if (player_want.y > playerY)
				d = 1;
	
			else if (player_want.x > playerX)
				d = 2;
	
			else if (player_want.y < playerY)
				d = 3;
	
			else if (player_want.x < playerX)
				d = 4;
		}
		
		switch (d)
		{
			// up
			case 1:
				wallinfo = Board->tile_status (playerX, playerY);

				// they cannot walk through the walls
				if (wallinfo == 1 || wallinfo == 3)
					returnVal = PLAYER_FAYUL;

				// they cannot be on the same spot hehehe
				else if (playerX == otherX && playerY+1 == otherY)
					returnVal = PLAYER_FAYUL;

				// the move is a success
				else
					returnVal = MOVE_SUCCESS;

				break;
			// right
			case 2:
				wallinfo = Board->tile_status (playerX, playerY);

				// again check for walls
				if (wallinfo == 2 || wallinfo == 3)
					returnVal = PLAYER_FAYUL;

				// again, they cannot move in the same spot
				else if (playerY == otherY && playerX+1 == otherX)
					returnVal = PLAYER_FAYUL;

				// a successful move
				else
					returnVal = MOVE_SUCCESS;

				break;
			// down
			case 3:
				wallinfo = Board->tile_status (playerX, playerY-1);
	
				if (wallinfo == 1 || wallinfo == 3)
					returnVal = PLAYER_FAYUL;

				else if (playerX == otherX && playerY-1 == otherY)
					returnVal = PLAYER_FAYUL;

				else
					returnVal = MOVE_SUCCESS;

				break;
			// left
			case 4:
				wallinfo = Board->tile_status (playerX-1, playerY);
	
				if (wallinfo == 2 || wallinfo == 3)
					returnVal = PLAYER_FAYUL;

				if (playerY == otherY && playerX-1 == otherX)
					returnVal = PLAYER_FAYUL;

				else
					returnVal = MOVE_SUCCESS;

				break;
			// error ...
			default:
				std::cout << "Error! Unknown direction.\nExiting!" << std::endl;
				exit (EXIT_FAILURE);
		}
	}

	return returnVal;
}

// we check if player is trying to move walls to a valid position
// ...
int
engine::check_wall (trn player_want)
{
	// walls have size '2' so we have to check for one more side left
	int wall_orig 	= Board->tile_status (player_want.x, player_want.y),
	    size_x	= Board->getX (),
	    size_y	= Board->getY (),
	    ourX	= Board->get_px (turn % 2),
	    ourY	= Board->get_py (turn % 2),
	    returnVal	= WALL_SUCCESS;


	// we check if we have enough walls
	if (p [turn % 2]->get_walls () < 1)
		returnVal = PLAYER_FAYUL;

	// check if the walls go overboard in x-direction
	if (player_want.wall == 1 && player_want.x == size_x-1)
		returnVal = PLAYER_FAYUL;

	// check if walls go overboard in y-direction
	if (player_want.wall == 2 && player_want.y == size_y-1)
		returnVal = PLAYER_FAYUL;

	if (returnVal != PLAYER_FAYUL)
	{
		// we check for a valid move
		if (player_want.wall == 1)
		{
			int wall_next	= Board->tile_status (player_want.x + 1,
					player_want.y),
			    path	= find_path (ourX, ourY);

			// there already is a wall on the tile in the same position
			if (wall_orig == 1 || wall_orig == 3)
				returnVal = PLAYER_FAYUL;

			// there is already a wall on the adjacent tile in the same position
			else if (wall_next == 1 || wall_next == 3)
				returnVal = PLAYER_FAYUL;

			// we check if this criples either of players
			// a) does it cripple us?
			else if (path >= size_x * size_y * 4)
				returnVal = PLAYER_FAYUL;

			// b) does it cripple our opponent
			else
			{
				int otherX = Board->get_px ((turn + 1) % 2),
				    otherY = Board->get_py ((turn + 1) % 2);

				path = find_path (otherX, otherY);
				if (path >= size_x * size_y * 4)
					returnVal = PLAYER_FAYUL;
			}
		}
		
		else if (player_want.wall == 2)
		{
			int wall_next	= Board->tile_status (player_want.x,
					player_want.y + 1),
			    path	= find_path (ourX, ourY);

			// cannot build over the same wall on current square
			if (wall_orig == 2 || wall_orig == 3)
				returnVal = PLAYER_FAYUL;

			// cannot build over the wall on the adjacent square
			else if (wall_next == 2 || wall_next == 3)
				returnVal = PLAYER_FAYUL;

			// we check if this criples either of players
			// a) does it cripple us?
			else if (path >= size_x * size_y * 4)
				returnVal = PLAYER_FAYUL;

			// b) does it cripple our opponent
			else
			{
				int otherX = Board->get_px ((turn + 1) % 2),
				    otherY = Board->get_py ((turn + 1) % 2);

				path = find_path (otherX, otherY);
				if (path >= size_x * size_y * 4)
					returnVal = PLAYER_FAYUL;
			}
		}

		else
		{
			std::cout << "Error! Unknown wall specification!\nExiting." << std::endl;
			exit (EXIT_FAILURE);
		}
	}
	
	return returnVal;
}

// a primitive algorithm, that cheks if the players are walled in
// ... it will do for now
int
engine::find_path (int a, int b)
{
	int size_x	= Board->get_px (turn % 2),
	    size_y	= Board->get_py (turn % 2),
	    counter	= 0,
	    success	= 0;

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
	if (turn%2 == 0)
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
	else
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

// check for victory
int
engine::check_victory ()
{
	int returnVal = CONTINUE_GAME;

	if (p [0]->get_y () == Board->getY ())
		returnVal = P1_WON;

	else if (p [1]->get_y () == 0)
		returnVal = P2_WON;

	return returnVal;
}

