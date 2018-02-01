// Board is used for the board class

#include "Board.h"

using namespace std;

//=============================================================================

// Board default constructor
Board::Board()
{
	numLines = 1;
	numColumns = 1;
	boardArea = 1;
}

//----------------------------------------------------------------------------

// Ship constructor, using a file with the name "filename"
Board::Board(const string &filename)
{
	shipArea = 0;
	ifstream filein;
	stringstream ss;
	string line;
	char ignore;

	filein.open(filename);
	getline(filein, line);

	// Store the board Lines and Columns
	ss << line;
	ss >> numLines >> ignore >> numColumns;

	boardArea = numLines* numColumns;

	// Creates empty board
	initializeBoard(numLines, numColumns);

	// Stores the ship vector
	while (!filein.eof())
	{
		ss.clear();
		ss.str("");

		char symbol;
		Position<char> position;
		char orientation;
		unsigned int size;
		unsigned int color;

		getline(filein, line);

		ss << line;
		ss >> symbol >> size >> position.lin >> position.col >> orientation >> color;

		Ship insertShip(symbol, position, orientation, size, color);

		// Checks if it's possible to place the ships on the board

		bool sucess = checkOutside(insertShip);

		if (sucess)
			sucess = checkCollision(insertShip);

		if (sucess == false)
			cout << "Unable to place ship in the index " << (ships.size() - 1) << "." << endl;
		else
		{
			shipArea += insertShip.size;
			ships.push_back(insertShip);
			putShip(insertShip, (ships.size() - 1));
		}
	}
}

//----------------------------------------------------------------------------

// Board default constructor
void Board::initializeBoard(int numLines, int numColumns)
{
	for (int i = 0; i < numLines; i++)
	{
		vector<int> boardLine;

		for (int j = 0; j < numColumns; j++)
		{
			boardLine.push_back(-1);
		}
		board.push_back(boardLine);
	}
}

//----------------------------------------------------------------------------

vector<vector<int>> Board::getBoard()
{
	return board;
}

//----------------------------------------------------------------------------

vector<Ship> Board::getVectorShips()
{
	return ships;
}

//----------------------------------------------------------------------------

// Receives a Ship and returns a boolean that represents whether the ship is inside the board(true) or not(false)
bool Board::checkOutside(const Ship &s)
{
	if (s.orientation == 'H')
	{
		if (((s.position.col + s.size) > numColumns) || ((unsigned int)s.position.lin >= numLines))
		{
			return false;
		}
	}
	else
	{
		if (((s.position.lin + s.size) > numLines) || ((unsigned int)s.position.col >= numColumns))
		{
			return false;
		}
	}
	return true;
}

//----------------------------------------------------------------------------

// Receives a Ship and returns a boolean that represents whether the ship is not colliding with another ship(true) or it is(false)
bool Board::checkCollision(const Ship&s)
{
	if (s.orientation == 'H')
	{
		for (unsigned int n = s.position.col; n < (s.position.col + s.size); n++)
		{
			if (board[s.position.lin][n] != -1)
			{
				return false;
			}
		}
	}
	else
	{
		for (unsigned int n = s.position.lin; n < (s.position.lin + s.size); n++)
		{
			if (board[n][s.position.col] != -1)
			{
				return false;
			}
		}
	}
	return true;
}

//----------------------------------------------------------------------------

// Receives a ship and adds it to the board, if possible. Doesn't return anything
void Board::putShip(const Ship &s, unsigned int index)
{
	if (s.orientation == 'H')
	{
		for (unsigned int n = s.position.col; n < (s.position.col + (s.size)); n++)
		{
			board[s.position.lin][n] = index;
		}
	}
	else
	for (unsigned int n = s.position.lin; n < (s.position.lin + (s.size)); n++)
	{
		board[n][s.position.col] = index;
	}
}

//----------------------------------------------------------------------------

// Receives a ship and removes it from the board. Doesn't return anything
void Board::removeShip(const Ship &s)
{
	if (s.orientation == 'H')
	{
		for (unsigned int n = s.position.col; n < (s.position.col + (s.size)); n++)
		{
			board[s.position.lin][n] = -1;
		}
	}
	else
	for (unsigned int n = s.position.lin; n < (s.position.lin + (s.size)); n++)
	{
		board[n][s.position.col] = -1;
	}
}

//----------------------------------------------------------------------------

void Board::moveShips() // tries to randmonly move all the ships of the fleet
{
	for (unsigned int i = 0; i < ships.size(); i++)
	{

		Ship newShip = ships[i];

		if(!newShip.isDestroyed())
		{
			newShip.moveRand(numLines, numColumns);

			removeShip(ships[i]);

			bool sucesso;
			sucesso = checkOutside(newShip);

			if (sucesso)
				sucesso = checkCollision(newShip);

			if (sucesso)
			{
				putShip(newShip, i);
				ships[i] = newShip;
			}
			else
				putShip(ships[i], i);
		}
	}
}

//----------------------------------------------------------------------------

int Board::shipPart(int X, int Y) const
{
	int shipPart;

	if (ships[board[X][Y]].orientation == 'H')
		shipPart = Y - (ships[board[X][Y]].position.col);
	else
		shipPart = X - (ships[board[X][Y]].position.lin);

	return shipPart;
}

//----------------------------------------------------------------------------

bool Board::attack(Bomb &b) // attacks the board with a bomb
{
	b.simulateError(numLines - 1, numColumns - 1);
	Position<int> targetInt = PCharToInt(b.target);
	int L = targetInt.lin;
	int C = targetInt.col;

	if (board[L][C] == -1)
	{
		// Hit the sea
		cout << "You hit the sea" << endl;
		return false;
	}

	else
	{
		// Hits a ship
		if (ships[board[L][C]].attack(shipPart(L, C)))
		{
			if (ships[board[L][C]].isDestroyed()) // checks if the ship has been destroyed
			{
				// Ship was destroyed
				cout << "You have destroyed the: " << ships[board[L][C]].symbol << endl;
				removeShip(ships[board[L][C]]);
			}
			else
			{
				// Ship was hit
				cout << "You have hit the: " << ships[board[L][C]].symbol << endl;
			}
			return true;
		}

		else
		{
			// Hit an already destroyed part
			cout << "You hit a wreckage" << endl;
			return false;
		}
	}
}

//----------------------------------------------------------------------------

void Board::show() const // shows the attributes of the board (for debugging)
{
	cout << "Number of Columns: " << numColumns << endl << "Number of Lines: " << numLines << endl << endl;

	for (unsigned int i = 0; i < ships.size(); i++)
		cout << ships[i];
}

//----------------------------------------------------------------------------

void Board::colorCheck(int X, int Y) const // processes ship color
{
	for (unsigned int i = 0; i < ships.size(); i++)
	{
		if (board[Y][X] == i)
			setcolor(ships[i].color, 1);
	}
}

//----------------------------------------------------------------------------

// Overloads the operator << to create a display function (for debugging)
ostream& operator<<(ostream& out, const Board& b)
{
	// Clears the screen
	clrscr();

	// Writes the top of the Board
	out << " ";
	int asciiA = 65;
	int asciia = 97;

	for (unsigned int k = 0; k < b.numColumns; k++)
	{
		out << " " << (char)asciia;
		asciia++;
	}

	out << endl;

	for (unsigned int i = 0; i < b.numLines; i++)
	{
		// Writes the board's left side
		out << (char)asciiA;
		asciiA++;

		// Writes the board content
		for (unsigned int j = 0; j < b.numColumns; j++)
		{
			setcolor(1, 1);
			b.colorCheck(j, i);
			if (b.board[i][j] >= 0)
			{
				out << " " << b.ships[b.board[i][j]].status[(b.shipPart(i, j))];
			}
			else
				out << " " << '.';
			setcolor(7, 0);
		}

		out << endl;
	}
	out << endl;

	return out;
}

//=============================================================================