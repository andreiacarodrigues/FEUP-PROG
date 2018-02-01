// Score Manager is used for the scores logic

#ifndef SCORES_H
#define SCORES_H

#include "Player.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

//=============================================================================
struct Score
{
	std::string name;
	double value;
	int shipsArea;
	int boardArea;
};
//=============================================================================
class ScoreManager
{
public:
	ScoreManager(double &WinnerScore, Player p, std::string filename); // Constructs a ScoreManager from an initial score file
	void bubblesort(std::vector<Score> &v); // Sorts the ScoreList using Value as primary key, returns nothing
	void PrintScore(); // Prints the new ScoreList to a file
private:
	std::vector <Score> ScoreList;
};
//=============================================================================

#endif
