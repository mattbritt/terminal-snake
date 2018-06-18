/**********************************************************************
**	Space.cpp
**	Author: Matt Britt
**	Date: 11/30/2017
**	Description:   Space.cpp is the implementation file for the Space class.
**				The Space class is an abstract based class for space objects
**				in the Snake game.
*********************************************************************/

#include "Space.hpp"

string getANSIColor(ANSIColor color);

/********************************************************************
**  Space() constructor
**	Description:  Initialize space object
*********************************************************************/
Space::Space()
{

}

/********************************************************************
**  char getSymbol()
**	Description:  Getter, returns symbol character
*********************************************************************/
char Space::getSymbol()
{
	return symbol;
}

/********************************************************************
**  void setSymbol(char symbol)
**	Description:  Setter, sets symbol
*********************************************************************/
void Space::setSymbol(char symbol)
{
	this->symbol = symbol;
}

/********************************************************************
**  Space* getSpace(Direction dir)
**	Description:  Getter, returns Space pointer for given direction
*********************************************************************/
Space* Space::getSpace(Direction dir)
{
	switch (dir)
	{
	case UP:
		return spaceUp;
		break;

	case DOWN:
		return spaceDown;
		break;
	
	case LEFT:
		return spaceLeft;
		break;
	
	case RIGHT:
		return spaceRight;
		break;
	}

	return nullptr;			// if invalid direction given
}

/********************************************************************
**  void setSpace(Direction dir, Space *ptr)
**	Description:  setter, sets space in given dir to *ptr
*********************************************************************/
void Space::setSpace(Direction dir, Space *ptr)
{
	switch (dir)
	{
	case UP:
		spaceUp = ptr;
		break;
		
	case DOWN:
		spaceDown = ptr;
		break;

	case LEFT:
		spaceLeft = ptr;
		break;

	case RIGHT:
		spaceRight = ptr;
		break;
	}
}


/********************************************************************
**  ANSIColor getColor()
**	Description:  Getter, returns foreground ANSIColor of space
*********************************************************************/
ANSIColor Space::getColor()
{
	return color;
}

/********************************************************************
**  void setColor(ANSIColor color)
**	Description:  Setter, sets foreground ANSIColor of space
*********************************************************************/
void Space::setColor(ANSIColor color)
{
	this->color = color;
}

/********************************************************************
**  ANSIColor getBackColor()
**	Description:  Getter, returns background ANSIColor of space
*********************************************************************/
ANSIColor Space::getBackColor()
{
	return backColor;
}

/********************************************************************
**  void setBackColor(ANSIColor color)
**	Description:  Setter, sets background ANSIColor of space
*********************************************************************/
void Space::setBackColor(ANSIColor color)
{
	this->backColor = color;
}

/********************************************************************
**  bool hasUpdated()
**	Description:  Returns true if space has updated since last read
*********************************************************************/
bool Space::hasUpdated()
{
	return update;
}

/********************************************************************
**  string read()
**	Description:  Returns string for output to screen
*********************************************************************/
string Space::read()
{
	// set update flag
	update = false;

	string retString = ANSI_ColorToCodeForeGround(color);		// foreground color
	retString += ANSI_ColorToCodeBackGround(backColor);			// background color
	retString += symbol;										// symbol
	//retString += "\033[0m";

	return (retString);
}

/********************************************************************
**  string read(ANSIColor foreColor, ANSIColor backColor)
**	Description:  Returns string for output to screen; Does not output
**					unnecessary color strings
*********************************************************************/
string Space::read(ANSIColor foreColor, ANSIColor bColor)
{
	// set update flag
	update = false;

	string retString;

	// check if foreground color has changed
	if (foreColor != color)
	{
		retString = ANSI_ColorToCodeForeGround(color);				// foreground color string
	}

	// check if background color has changed
	if (bColor != backColor)
	{
		retString += ANSI_ColorToCodeBackGround(backColor);			// background color string
	}

	retString += symbol;											// symbol char
		
	return (retString);
}

/********************************************************************
**  void setUpdate(bool doUpdate)
**	Description:  Setter, sets update flag (true by default)
*********************************************************************/
void Space::setUpdate(bool doUpdate)
{
	update = doUpdate;
}

/********************************************************************
**  void setTraversable(bool trav)
**	Description:  Setter, sets traversable
*********************************************************************/
void Space::setTraversable(bool trav)
{
	traversable = trav;
}

/********************************************************************
**  bool getTraversable()
**	Description:  Getter, returns traversable
*********************************************************************/
bool Space::getTraversable()
{
	return traversable;
}



