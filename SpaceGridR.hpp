/**********************************************************************
**	SpaceGridR.hpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   SpaceGridR.hpp is the header file for the SpaceGridR class.
**				The SpaceGridR class represents the grid of spaces in the main
**				game area and offers background restore.  The SpaceGridR class
**				inherits the SpaceGrid class.
*********************************************************************/

#ifndef SPACEGRIDR_HPP
#define SPACEGRIDR_HPP

#include "SpaceGrid.hpp"

class SpaceGridR : public SpaceGrid
{
private:
	SpaceGrid foreGrid;
	SpaceGrid backGrid;

public:
	// override the parseGrid function to fill fore and back ground grids
	virtual ParseLabels parseGrid(string line, ParseLabels label) override;
	
	// returns a vector of strings to update screen
	virtual void getUpdate(vector<string> &updateVector);

	// adds new space at row, col; return true on success, false on fail
	virtual bool addSpace(int row, int col, Space *newPtr);
	virtual Space* getSpace(int row, int col);			// overriden getter, returns space

	void restoreSpace(int row, int col);				// restores a space to the background

	virtual LevelInfo getLevelInfo() override;			// getter, returns levelInfo 
};

#endif
