/*
Name: The Battleship Game.
Description: A Battleship Game in CPP.
Created by: Andreia Rodrigues, Eduardo Leite.
Date: 2015-05-25.
*/ 
#include "GameManager.h"
#include "Scores.h"
#include <ctime>

using namespace std;

int main()
{
	double WinnerScore;

	// Feeds a new seed into the random number generator
	srand((unsigned int)(time(NULL)));

	// Initializes our game manager
	GameManager GM;

	// Calls game manager's function load game
	GM.loadGame();

	// While the game is running call the function that processes de game turn
	while(GM.gameIsRunning)
		GM.gameTurn();

	// Initializes our score manager
	ScoreManager SM(WinnerScore, GM.Players[GM.currentPlayer], "Scores.txt");

	// Prints the score
	SM.PrintScore();

	// Announces the winner
	clrscr();
	cout << "And the winner is: " << GM.Players[GM.currentPlayer].getName() << endl;
	cout << "With a score of: " << WinnerScore << endl;

	return 0;
}