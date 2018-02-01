// Game Manager is used for the game logic

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Player.h"

//=============================================================================
class GameManager
{
public:
	// Functions
	GameManager(); // Initializes the game manager
	void loadGame(); // Loads the configurations
	void gameTurn(); // Processes de game time

	// Variables
	bool gameIsRunning; // If the game is running or not
	bool debug; // If the debug mode is on
	std::vector<Player> Players; // Player vector
	int coinToss; // To determine who playes first
	int currentPlayer; // The player who has the turn
	int enemyPlayer; // The enemy Player
};
//=============================================================================

#endif