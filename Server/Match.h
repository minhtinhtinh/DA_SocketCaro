/*
* This's socket and some structures for project
* @author
* - Nguyen Phuc Loi
* - 1660321
* @email
* - nploi1998@gmail.com
*/

#pragma once

#include "Player.h"
#include <vector>
#include <sstream>
#include "..\lib\Map.h"
#include <queue>

using namespace std;

/*
class of match
include player1, player2, and thread
*/
class Match {
public:
	Match(){

	}

	/*
	@describe
		Add player for game
	@param
		player: player
	@return
		NULL
	*/
	void addPlayer(Player player);

	~Match() {

	}

public:
	vector<Player> players;
	pthread_t thread;
};