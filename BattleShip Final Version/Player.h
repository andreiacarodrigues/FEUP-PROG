// Player is used for the player class

#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

//=============================================================================
class Player
{
	friend class GameManager;
	friend class ScoreManager;
	friend std::ostream& operator<<(std::ostream& out, const Player& p); // Overloads the operator << to create a display function (for debugging)

public:
	Player(std::string playerName, std::string boardFilename);
	std::string getName();
	Bomb getBomb() const; // asks bomb target coordinates and creates the bomb
	bool attackBoard(Bomb &b); // "receives" a bomb from the opponent
private:
	std::string name; // name of the player
	Board board; // board of the player
	time_t time;
};
//=============================================================================

#endif