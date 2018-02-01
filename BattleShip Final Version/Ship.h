// Ship is used for the ship class

#ifndef SHIP_H
#define SHIP_H

#include "Utilities.h"

//=============================================================================
class Ship
{
	friend class Board;
	friend std::ostream& operator<<(std::ostream& out, const Ship& s); // Overloads the operator << to create a display function (for debugging)
	friend std::ostream& operator<<(std::ostream& out, const Board& b); // Overloads the operator << to create a display function (for debugging)
public:
	Ship(char symbol, Position<char> position, char orientation, unsigned int size,unsigned int color); // Ship constructor
	bool attack(size_t partNumber); // partNumber = {0,1,…, size-1}
	void swapOrientation(); // Swaps the ship orientation
	void move(char direction, bool rotate, unsigned int MaxLine, unsigned int MaxCol); // Moves the boat
	void moveRand(unsigned int MaxLine, unsigned int MaxCol); // Moves the ship randomly
	bool isDestroyed() const; // Checks whether the ship is destroyed or not
	char getShipSymbol() const; // Returns the ship symbol
	Position<int> getShipPosition() const; // Returns the ship position
	char getShipOrientation() const; // Returns the ship orientation
	unsigned int getShipSize() const; // Returns the ship size
	unsigned int getShipColor() const; // Returns the ship color
	std::string getShipStatus() const; // Returns the ship status
private:
	char symbol; // 'P' = "porta-aviões"; 'F' = "fragata"; …
	Position<int> position; // coordinates of the upper left corner of the ship
	char orientation; // 'H' = horizontal; 'V' = vertical
	unsigned int size; // number of cells occupied by the ship, on the board
	unsigned int color; // color code: 0=BLACK, 1=BLUE, …
	std::string status; // status[i]: upper case = good; lower case = damaged
};
//=============================================================================

#endif