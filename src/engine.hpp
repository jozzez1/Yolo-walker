#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#include <stdlib.h>

#include "game.hpp"
#include "player.hpp"
#include "board.hpp"

class Engine
{
	private:
		int turn;
	
		player ** p;
		board * Board;

	public:
		// constructor/destructor
		Engine (int, string, string, int, int);
		~Engine ();

		// functions that give turns to players
		int make_turn ();
		trn give_turn ();

		// functions that check the validity of
		// the turn
		int check_turn (trn);
		int check_move (trn);
		int check_wall (trn);
		int find_path (int,int);

		// function that checks game-over
		int check_victory ();
};

#endif
