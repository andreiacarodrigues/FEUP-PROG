// Ship is used for the ship class

#include "Ship.h"
using namespace std;

//=============================================================================

// Ship constructor, using all of the ship attributes
Ship::Ship(char symbol, Position<char> position, char orientation, unsigned int size,unsigned int color)
{
	Ship::symbol = symbol;
	Ship::position = PCharToInt(position);
	Ship::orientation = orientation;
	Ship::size = size;
	Ship::color = color;

	for(unsigned int i = 0; i < Ship::size; i++)
	{
		status += symbol;
	}
}

//----------------------------------------------------------------------------

// Receives a size_t partNumber, attemps to "attack" the ship and returns a bool that represents the sucess of the operation
bool Ship::attack(size_t partNumber)
{ 
	if(isupper(status[partNumber]))
	{
		// Hits a non previously hit part of the ship
		status[partNumber] = tolower(status[partNumber]);
		return true;
	}
	else
	{
		// Hit an already destroyed part
		return false;
	}
}

//----------------------------------------------------------------------------

// Swaps the ship orientation, doesn't return anything
void Ship::swapOrientation()
{
	if(orientation == 'H')
		orientation = 'V';
	else
		orientation = 'H';
}

//----------------------------------------------------------------------------

// Moves the ship using a direction, rotation and two board limits, doesn't return anything
void Ship::move(char direction, bool rotate, unsigned int MaxLine, unsigned int MaxCol) // moves the boat
{
	if(rotate)
		swapOrientation();

	switch(direction)
	{
	case 'O':
		break;
	case 'N':
		if(position.lin > 0)
			position.lin--;
		break;
	case 'S':
		if((unsigned int)position.lin < (MaxLine - 1))
			position.lin++;
		break;
	case 'E':
		if(position.col > 0)
			position.col--;
		break;
	case 'W':
		if((unsigned int)position.col < (MaxCol - 1))
			position.col++;
		break;
	}
}

//----------------------------------------------------------------------------

// Generates a random direction and rotation for the function move from two board limits, deosn't return anything
void Ship::moveRand(unsigned int MaxLine, unsigned int MaxCol) // moves the ship randomly
{
	int OrientationSelector = randomBetween(0,1);
	int MovementSelector = randomBetween(0,4);

	char direction = ' ';
	bool rotate = false;

	switch(OrientationSelector)
	{
	case 0:
		rotate = false;
		break;
	case 1:
		rotate = true;
		break;
	}

	switch(MovementSelector)
	{
	case 0:
		direction = 'O';
		break;
	case 1:
		direction = 'N';
		break;
	case 2:
		direction = 'S';
		break;
	case 3:
		direction = 'E';
		break;
	case 4:
		direction = 'W';
		break;
	}

	move(direction, rotate, MaxLine, MaxCol);
}

//----------------------------------------------------------------------------

// Doesn't receive anything, returns a boolean that represents whether the ship is destroyed(true) or not(false)
bool Ship::isDestroyed() const // checks whether the ship is destroyed
{
	float halfShip = (float)Ship::size / 2;
	float damagedParts = 0;

	for(unsigned int i = 0; i < Ship::size; i++)
	{
		if(islower(status[i]))
			damagedParts++;
	}

	if(damagedParts >= halfShip)
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------

// Overloads the operator << to create a display function (for debugging)
ostream& operator<<(ostream& out, const Ship& s)
{
	out << "Symbol: " << s.symbol << endl;
	out << "Line: " << s.position.lin << endl;
	out << "Column: " << s.position.col << endl;
	out << "Orientation: " << s.orientation << endl;
	out << "Size: " << s.size << endl;
	out << "Color: " << s.color << endl;
	out << "Status: ";

	for(unsigned int i = 0; i < s.size; i++)
	{
		out << s.status[i];
	}

	out << endl << endl;

	return out;
}

//----------------------------------------------------------------------------
char Ship::getShipSymbol() const
{
	return symbol;
}
//----------------------------------------------------------------------------
Position<int> Ship::getShipPosition() const
{
	return position;
}
//----------------------------------------------------------------------------
char Ship::getShipOrientation() const
{
	return orientation;
}
//----------------------------------------------------------------------------
unsigned int Ship::getShipSize() const
{
	return size;
}
//----------------------------------------------------------------------------
unsigned int Ship::getShipColor() const
{
	return color;
}
//---------------------------------------------------------------------------
string Ship::getShipStatus() const // returns the ship status
{
	return status;
}
//=============================================================================