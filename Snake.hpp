/**********************************************************************
**	Snake.hpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   Snake.hpp is the header file for the Snake class.
**				The Snake class represents the snake in game
*********************************************************************/

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <deque>
#include <string>

#include "Direction.hpp"
#include "ANSI_Codes.hpp"
#include "SpaceGridR.hpp"
#include "SnakeSpace.hpp"
#include "EventObj.hpp"

using std::deque;
using std::string;

struct snakeSegment {											// represents segment of snake in body deque
	int row;
	int col;
};


class Snake
{
private:
	EventObj eventObj;											// passes event messages

	deque<snakeSegment> body;									// represents the snake

	Direction headDir = NO_DIR;									// current direction
	Direction lastDir = NO_DIR;									// direction of previous snake segment (neck)

	SpaceGridR *gridPtr = nullptr;								// point the grid for update

//	int extendingSegments = 0;									// number 

public:
	Snake(int row, int col, SpaceGridR &grid);					// constructor

	void updateGrid();											// updates grid with snake

	void moveSnake(Direction dir);								// moves snake in given dir
	void moveForward();											// moves snake forward one space
	
	bool validMove(int row, int col);							// checks if space is valid or not
};

#endif

