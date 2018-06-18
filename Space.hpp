/**********************************************************************
**	Space.hpp
**	Author: Matt Britt
**	Date: 11/30/2017
**	Description:   Space.hpp is the header file for the Space class.
**				The Space class is an abstract based class for space objects
**				in the Snake game.
*********************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include <string>

#include "Direction.hpp"
#include "EventObj.hpp"
#include "ANSI_Codes.hpp"

using std::string;
using std::to_string;


class Space
{
protected:
	EventObj eventObj;									// communicates events

	Space *spaceUp	= nullptr;							// pointer to space up from this one
	Space *spaceDown = nullptr;							// pointer to space down from this one
	Space *spaceLeft = nullptr;							// pointer to space left of this one
	Space *spaceRight = nullptr;						// pointer to space right of this one

	char symbol;										// character to display for this space
	
	ANSIColor color = WHITE;							// color for this space
	ANSIColor backColor = BLACK;						// background color

	bool traversable;
	bool update = true;									// tracks if screen needs to update this space

public:
	Space();											// constructor

	char getSymbol();									// getter returns symbol
	void setSymbol(char symbol);						// setter sets symbol

	bool getTraversable();								// getter, returns traversable
	void setTraversable(bool trav);						// setter, sets traversable

	Space* getSpace(Direction dir);						// getter, returns Space pointer for given direction
	void setSpace(Direction dir, Space *ptr);			// setter, sets space in given dir to *ptr

	ANSIColor getColor();								// getter, returns foreground ANSIColor of space
	void setColor(ANSIColor color);						// setter, sets foreground ANSIColor of space

	ANSIColor getBackColor();							// getter, returns background color
	void setBackColor(ANSIColor color);					// setter, set background color

	bool hasUpdated();									// returns true if space updated since last read
	void setUpdate(bool doUpdate = true);				// setter to set update flag (true by default)

	string read();										// reads space string for output
	string read(ANSIColor foreColor, ANSIColor bColor); // doesn't output unnecessary color strings

	// pure virtual functions
	virtual void checkForEvent() = 0;					// emits events				
	virtual Space* create() = 0;						// virtual create allows for clone
	virtual Space* clone() = 0;							// virtual clone allows all spaces to be cloned
};

#endif


