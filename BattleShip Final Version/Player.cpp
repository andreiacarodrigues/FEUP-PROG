// Player is used for the player class

#include "Player.h"
using namespace std;

//=============================================================================

Player::Player(string playerName, string boardFilename)
{
	name = playerName;
	board = Board(boardFilename);
	time = 0;
}

//----------------------------------------------------------------------------

string Player::getName()
{
	return name;
}

//----------------------------------------------------------------------------

Bomb Player::getBomb() const  // asks bomb target coordinates and creates the bomb
{
	Position<char> targetPosition;
	bool validCoordinates = false;
	Bomb bombReturn;
	string test;

	while (!validCoordinates)
	{
		test = "";
		cout << "What is the bomb target? (Ex: Cb)" << endl;
		getline(cin, test);

		if (cin.fail())
		{
			cout << endl << "Invalid input. " << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else if (test.length() != 2)
		{
			cout << endl << "Syntax wrong. " << endl;
		}
		else
		{
			targetPosition.lin = test[0];
			targetPosition.col = test[1];

			Position<int> targetPositionTemp = PCharToInt(targetPosition);

			if ((unsigned int)targetPositionTemp.lin > board.numLines || (unsigned int)targetPositionTemp.col > board.numColumns)
			{
				cout << endl << "Invalid line/column. " << endl;
			}
			else
			{
				bombReturn = Bomb(targetPosition);
				validCoordinates = true;
			}
		}
	}

	return bombReturn;
}

//----------------------------------------------------------------------------

bool Player::attackBoard(Bomb &b) // "receives" a bomb from the opponent
{
	bool attackShip;
	attackShip = board.attack(b);

	return attackShip;
}

//----------------------------------------------------------------------------

ostream& operator<<(std::ostream& out, const Player& p)
{
	out << p.board;
	out << p.name << "'s board." << endl << endl;

	return out;
}

//=============================================================================