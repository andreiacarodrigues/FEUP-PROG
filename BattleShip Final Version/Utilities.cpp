// Utilities is used for auxiliary functions and structures

#include "Utilities.h"

//=============================================================================

// Receives a Position<Char> and returns a Position<Int>
Position<int> PCharToInt (Position<char> PosC)
{
	Position<int> PosI;
	
	PosI.col = (int)(PosC.col - 97);
	PosI.lin = (int)(PosC.lin - 65);

	return PosI;
}

//----------------------------------------------------------------------------

Position<char> PIntToChar (Position<int> PosI) // converts PositionInt to PositionChar
{
	Position<char> PosC;
	
	PosC.col = (char)(PosI.col + 97);
	PosC.lin = (char)(PosI.lin + 65);

	return PosC;
}

//----------------------------------------------------------------------------

// Receives two integer values and returns a pseudo random number between those two values
int randomBetween(int n1, int n2)
{
	if(n1 < n2)
		return n1 + rand() % (n2 - n1 + 1);
	else
		return n2 + rand() % (n1 - n2 + 1);
} 

//=============================================================================