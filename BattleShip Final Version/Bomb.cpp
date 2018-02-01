// Bomb is used for the bomb class

#include "Bomb.h"

using namespace std;

//=============================================================================

// Bomb default constructor
Bomb::Bomb()
{
	target.lin = 'A';
	target.col = 'a';
}

//----------------------------------------------------------------------------

// Bomb constructor, using a Position Char
Bomb::Bomb(Position<char> targetPosition)
{
	target = targetPosition;
}

//----------------------------------------------------------------------------

// Bomb get function, returns a const Position Char
Position<char> Bomb::getTargetPosition() const 
{
	return target;
}

//----------------------------------------------------------------------------

// Simulates the manufacturing error, receives a bomb and returns the modified bomb
void Bomb::simulateError(unsigned int MaxLines,unsigned int MaxColumns)
{
	int LineOffset;
	int ColumnOffset;

	LineOffset = randomBetween(-1, 1);
	ColumnOffset = randomBetween(-1, 1);

	Position<int> targetInt = PCharToInt (target);

	targetInt.lin += LineOffset;

	if(targetInt.lin < 0 || (unsigned int)targetInt.lin > MaxLines)
		targetInt.lin -= LineOffset;

	targetInt.col += ColumnOffset;

		if(targetInt.col < 0 || (unsigned int)targetInt.col > MaxColumns)
		targetInt.col -= ColumnOffset;

	target = PIntToChar(targetInt);
}

//----------------------------------------------------------------------------

// Overloads the operator << to create a display function (for debugging)
ostream& operator<<(ostream& out, const Bomb& b)
{
	out << "Target Line: " << b.target.lin << endl << "Target Column: " << b.target.col << endl << endl;
	return out;
} 

//===========================================================================