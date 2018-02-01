// Utilities is used for auxiliary functions and structures

#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include <iostream>

//=============================================================================

// A simple template struct to store coordinates in multiple data types
template<class Point>
struct Position
{
	Point lin, col;
};

//-----------------------------------------------------------------------------

// Receives a Position<Char> and returns a Position<Int>
Position<int> PCharToInt (Position<char> PosC);

//-----------------------------------------------------------------------------

// Receives a Position<Int> and returns a Position<Char>
Position<char> PIntToChar (Position<int> PosI);

//-----------------------------------------------------------------------------

// Receives two integer values and returns a pseudo random number between those two values
int randomBetween(int n1, int n2);

//=============================================================================

#endif