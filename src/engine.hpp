#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#include "game.hpp"
#include "player.hpp"
#include "board.hpp"

class engine
{
	private:
		int turn;
	
		player ** p;
		board * Board;

	public:
		// constructor/destructor
		engine (int, string, string, int, int);
		~engine ();

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
