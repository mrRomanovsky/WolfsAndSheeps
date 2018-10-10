#pragma once
#include <iostream>

class Position
{
public:
	Position(int x, int y);
	Position();
	~Position();
	int row;
	int col;
	bool operator==(Position& p);
	bool operator!=(Position& p);
private:
};

bool correct_position(int x, int y)
{
	return x >= 0 && y >= 0 && x < 8 && y < 8;
}

Position::Position(int x, int y)
{
	this->row = x;
	this->col = y;
}

inline Position::Position()
{
	row = 0; 
	col = 0;
}

Position::~Position()
{
}

inline bool Position::operator==(Position & p)
{
	return row == p.row && col == p.col;
}

inline bool Position::operator!=(Position & p)
{
	return !(this->operator==(p));
}
