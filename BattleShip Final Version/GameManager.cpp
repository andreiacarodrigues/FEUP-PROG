// Game Manager is used for the game logic

#include "GameManager.h"
#include <ctime>

using namespace std;

//=============================================================================

// Initializes the game manager
GameManager::GameManager()
{
	gameIsRunning = true;
	debug = false;
	coinToss = randomBetween(0, 1);
	currentPlayer = coinToss;
	enemyPlayer = (currentPlayer + 1) % 2;
}

//----------------------------------------------------------------------------

// Loads the configurations
void GameManager::loadGame()
{
	ifstream FileInTest;

	for (int i = 0; i <= 1; i++)
	{
		string namePlayer;
		string nameBoard;

		cout << "Player " << i + 1 << " enter your name (max 15 characters): ";
		getline(cin, namePlayer);

		do
		{
		cout << "Now enter your board: ";
		getline(cin, nameBoard);

		FileInTest.open(nameBoard);

		if(!FileInTest.is_open())
			cout << endl << "Invalid File" << endl;

		} while(!FileInTest.is_open());

		FileInTest.close();

		Players.push_back(Player(namePlayer, nameBoard));

		clrscr();
	}
}

//----------------------------------------------------------------------------

// Processes de game time
void GameManager::gameTurn()
{
	// Save the time at the turn start
	time_t initialTime = time(NULL);

	// Game Turn
	Bomb newBomb;

	cout << Players[enemyPlayer];
	newBomb = Players[currentPlayer].getBomb();
	Players[enemyPlayer].board.moveShips();
	cout << Players[enemyPlayer];
	Players[enemyPlayer].board.attack(newBomb);
	if(debug)
	{
		cout << endl << newBomb;
		for (unsigned int i = 0; i < Players[enemyPlayer].board.ships.size(); i ++)
			cout << endl << Players[enemyPlayer].board.ships[i];
	}
	cout << endl;
	system("pause");

	// Check if game ended
	gameIsRunning = false;

	for (unsigned int i = 0; i < Players[enemyPlayer].board.numLines; i++)
	{
		for (unsigned int j = 0; j < Players[enemyPlayer].board.numColumns; j++)
		{
			if (Players[enemyPlayer].board.board[i][j] >= 0)
				gameIsRunning = true;
		}
	}

	// Save the time at the turn end
	time_t finalTime = time(NULL);

	// Add the difference to the timer
	Players[currentPlayer].time += (finalTime - initialTime);

	if(!gameIsRunning)
		return;

	// Change Player
	int aux;
	aux = currentPlayer;
	currentPlayer = enemyPlayer;
	enemyPlayer = aux;
}

//=============================================================================