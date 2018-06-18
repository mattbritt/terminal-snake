/**********************************************************************
**	SpaceGridR.hpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   SpaceGridR.hpp is the header file for the SpaceGridR class.
**				The SpaceGridR class represents the grid of spaces in the main
**				game area and offers background restore.  The SpaceGridR class
**				inherits the SpaceGrid class.
*********************************************************************/

#include "SpaceGridR.hpp"

/********************************************************************
**  virtual ParseLabels parseGrid(string line, ParseLabels label) override
**	Description:  Overriden parseGrid to get data into both fore and back grids
*********************************************************************/
ParseLabels SpaceGridR::parseGrid(string line, ParseLabels label)
{
	foreGrid.parseGrid(line, label);
return	backGrid.parseGrid(line, label);
}

/********************************************************************
**  void restoreSpace(int row, int col)
**	Description:  Restores a space to the background
*********************************************************************/
void SpaceGridR::restoreSpace(int row, int col)
{
	Space *oPtr = nullptr;
		oPtr = backGrid.getSpace(row, col)->clone();

	foreGrid.addSpace(row, col, oPtr);
}

/********************************************************************
**  virtual void getUpdate(vector<string> &updateVector)
**	Description:  returns a vector of strings for screen update
*********************************************************************/
void SpaceGridR::getUpdate(vector<string> &updateVector)
{
	foreGrid.getUpdate(updateVector);
}

/********************************************************************
**  virtual bool addSpace(int row, int col Space *newPtr)
**	Description:  Overridden addSpace -- adds/updates a space
*********************************************************************/
bool SpaceGridR::addSpace(int row, int col, Space *newPtr)
{
	return foreGrid.addSpace(row, col, newPtr);
}

/********************************************************************
**  virtual Space* getSpace(int row, int col)
**	Description:  Overridden getter, returns space at row, col
*********************************************************************/
Space* SpaceGridR::getSpace(int row, int col)
{
	return foreGrid.getSpace(row, col);
}

/********************************************************************
**  virtual LevelInfo getLevelInfo()
**	Description:  Overridden getter, returns levelInfo
*********************************************************************/
LevelInfo SpaceGridR::getLevelInfo()
{
	return foreGrid.getLevelInfo();
}
