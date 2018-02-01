// Score Manager is used for the scores logic

#include "Scores.h"
#include <iomanip>
using namespace std;

//=============================================================================

// Sorts the ScoreList using Value as primary key, returns nothing
void ScoreManager::bubblesort(vector<Score> &v){
      bool swapped = true;
      int j = 0;
      Score tmp;
      while (swapped) 
	  {
            swapped = false;
            j++;
            for (unsigned int i = 0; i < v.size() - j; i++) {
                  if (v[i].value > v[i + 1].value) {
                        tmp = v[i];
                        v[i] = v[i + 1];
                        v[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}

//----------------------------------------------------------------------------

// Constructs a ScoreManager from an initial score file
ScoreManager::ScoreManager(double &WinnerScore, Player p,std::string filename)
{
	// Read the file

	ifstream fileIn;
	string line;
	stringstream ss;
	Score insertScore;

	fileIn.open(filename);

	// Ignores the first line
	getline(fileIn, line);

	// Get the first significant line
	if(!fileIn.eof())
		getline(fileIn, line);

	while(!fileIn.eof())
	{
		ss << line;
		ss >> insertScore.name >> insertScore.value >> insertScore.shipsArea >> insertScore.boardArea;
		ScoreList.push_back(insertScore);

		ss.str("");
		ss.clear();

		getline(fileIn, line);
	}

	fileIn.close();

	// Add the new score
	Score newScore;
	newScore.name = p.name;
	if(newScore.name.size() > 15)
		newScore.name = newScore.name.substr(0,15);

	newScore.boardArea = p.board.boardArea;
	newScore.shipsArea = p.board.shipArea;
	newScore.value = ((double)p.time * newScore.shipsArea) / newScore.boardArea;

	// Saves the winner score
	WinnerScore = newScore.value;

	ScoreList.push_back(newScore);

	bubblesort(ScoreList);
}

//----------------------------------------------------------------------------

// Prints the new ScoreList to a file
void ScoreManager::PrintScore()
{
	ofstream fileOut;
	stringstream ss;
	fileOut.open("Scores.txt");

	ss.clear();
	ss.str("");
	ss << setw(15) << "Name" << setw(15) << "Score" << setw(15) << "Ships Area" << setw(15) << "Board Area" << endl;
	fileOut << ss.str();

	for (unsigned int i = 0; (i < 10 && i < ScoreList.size()); i++) // só deixa escrever o ficheiro com 10 scores
	{
		ss.clear();
		ss.str("");
		ss << setw(15) << ScoreList[i].name << setw(15) << setprecision(5) << ScoreList[i].value << setw(15) << ScoreList[i].shipsArea << setw(15) << ScoreList[i].boardArea << endl;
		fileOut << ss.str();
	}

	fileOut.close();
}

//=============================================================================