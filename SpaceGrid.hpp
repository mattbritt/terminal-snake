/**********************************************************************
**	SpaceGrid.hpp
**	Author: Matt Britt
**	Date: 11/30/2017
**	Description:   SpaceGrid.hpp is the header file for the SpaceGrid class.
**				The SpaceGrid class represents the grid of spaces in the main
**				game area.
*********************************************************************/

#ifndef SPACEGRID_HPP
#define SPACEGRID_HPP

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::u32string;

#include "Space.hpp"
#include "EmptySpace.hpp"
#include "WallSpace.hpp"
#include "PointSpace.hpp"

// TODO: remove testspace
#include "TestSpace.hpp"

using std::string;
using std::to_string;
using std::ifstream;
using std::vector;


enum ElementType { WALL, EMPTY, SNAKE };						// type of space class to use
enum ParseLabels { NONE, LEVEL, CODES, COLORS, BACK_COLORS, START, END, ERROR };	// labels used to parse levels

struct ELEMENT {
	char character;										// character representing element
	ElementType type;									// type code (determines which class to use)
	ANSIColor color = DEFAULT;									// foreground color
	ANSIColor backColor = DEFAULT;								// background color
};

struct LevelInfo {										// contains level info
	string levelName;
	string levelDescription;
	int time = -1;
	int lives = -1;

	int snakeRow = 5;
	int snakeCol = 5;

	string nextLevel;
};


class SpaceGrid
{
private:

	// Constants:
	const int MAX_ROWS = 21;							// max rows					
	const int MAX_COLS = 80;							// max cols

	// Variables:
	int nextRow = 0;									// used to iterate rows

	Space *firstSpace = nullptr;						// top-left space, first row and column to access grid

	LevelInfo levelInfo;								// struct to pass level info up to Game
		
	vector<ELEMENT> elemVec;							// vector to hold elements for parse


public:
	SpaceGrid();										// constructor
	~SpaceGrid();										// destructor

	int getRows();										// getter, returns rows
	int getCols();										// getter, returns cols

	virtual bool addSpace(int row, int col, Space *newPtr);		// adds new space at row, col; return true on success, false on fail
	void updateDirections(int row, int col, Space *ptr);// updates directions of adjacent spaces

	void removeSpace(int row, int col);					// removes space from memory

	bool loadGrid(string fileName);						// loads grid from fileName
	void loadDefaultGrid();								// loads Default level on loadGrid Fail
	virtual ParseLabels parseGrid(string line, ParseLabels label);	// parse grid into memory

	Space* getSpace(int row, int col);					// getter returns space at row, column
	Space* operator()(int row, int col);				// overloaded () operator for getSpace

	virtual void getUpdate(vector<string> &updateVector);		// returns a vector of strings to update screen

	virtual LevelInfo getLevelInfo();							// getter, returns levelInfo 
};

#endif


