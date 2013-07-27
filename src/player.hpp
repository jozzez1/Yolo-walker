#ifndef __PLAYER
#define __PLAYER

#include <iostream>
#include <string>
#include "game.hpp"

using namespace std;

// the player class
class player
{
	private:
		int index,	// player 1,2, ... , n
		    walls,	// number of walls a player can still build
		    x,		// the current x-coordinate on the board
		    y;		// the current y-coordinate on the board

		string name;	// player's name
		
	public:

		// some self-explainatory functions
		trn get_input ();

		int get_walls() { return walls; }

		void move (int, int);
		void use_wall () { walls--; }

		// set starting x-coordinate
		// int setX ();

		// constructor
		player (int, int, int, int, string);

		// destructor
		~player ();
};

#endif
