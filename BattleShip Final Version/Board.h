// Board is used for the board class

#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include "Bomb.h"
#include "Colors.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

//=============================================================================
class Board
{
	friend class Player;
	friend class GameManager;
	friend class ScoreManager;
	friend std::ostream& operator<<(std::ostream& out, const Board& b); // Overloads the operator << to create a display function (for debugging)
public:
	Board(); // Board default constructor
	Board(const std::string &filename); // Ship constructor, using a file with the name "filename"
	void initializeBoard(int numLines, int numColumns); // Initializes an empty board
	std::vector<std::vector<int>> getBoard();
	std::vector<Ship> getVectorShips();
	bool checkOutside(const Ship&s); // Checks if the ship isn't outside the bounds of the board
	bool checkCollision(const Ship&s); // Check if the ship doesn't collide with another ship
	void putShip(const Ship &s, unsigned int index); // Receives a ship and adds it to the board, if possible. Doesn't return anything
	void removeShip(const Ship &s); // Receives a ship and removes it from the board. Doesn't return anything
	void moveShips(); // tries to randmonly move all the ships of the fleet
	int shipPart(int X, int Y) const;
	bool attack(Bomb &b); // attacks the board with a bomb
	void display(); // displays the colored board during the game
	void show() const; // shows the attributes of the board (for debugging)
	void colorCheck(int X, int Y) const; // processes ship color
private:
	unsigned int numLines, numColumns; // board size
	std::vector<Ship> ships; // ships that are placed on the board
	std::vector<std::vector<int>> board;
	int boardArea;
	int shipArea;
	/*
	each element indicates
    the index of a ship in the 'ships' vector
    (in the range 0..ships.size()-1) ;
    -1 is used to represent the sea
	*/
};
//=============================================================================

#endif