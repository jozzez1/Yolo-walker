#ifndef __GAME_ENGINE
#define __GAME_ENGINE

#include <iostream>
#include <string>
#include "player.h"
#include "board.h"

class engine
{
	private:
		int turn;
	
		player ** p;
		board * Board;

	public:

		engine (int, string, string, int, int);

		void make_turn ();
		int give_turn ();
		int check_turn ();
};
