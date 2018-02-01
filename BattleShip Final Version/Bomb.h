// Bomb is used for the bomb class

#ifndef BOMB_H
#define BOMB_H

#include "Utilities.h"

//=============================================================================
class Bomb
{
	friend class Board;
	friend std::ostream& operator<<(std::ostream& out, const Bomb& b); // Overloads the operator << to create a display function (for debugging)
public:
	Bomb(); // Bomb default constructor
	Bomb(Position<char> targetPosition); // Bomb constructor, using a Position Char
	Position<char> getTargetPosition() const; // Bomb get function
	void simulateError(unsigned int MaxLines,unsigned int MaxColumns); // Simulates the manufacturing error
private:
	Position<char> target;
};
//=============================================================================

#endif