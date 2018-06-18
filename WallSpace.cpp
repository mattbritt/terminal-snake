/**********************************************************************
**	WallSpace.cpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   WallSpace.cpp is the implmentation file for the WallSpace class.
**				The WallSpace class represents an empty (that is not traversable)
**				Space object.  WallSpace inherits the Space class.
*********************************************************************/

#include "WallSpace.hpp"

/********************************************************************
**  WallSpace() default constructor
**	Description:  Initialize WallSpace object
*********************************************************************/
WallSpace::WallSpace()
{
	
}

/********************************************************************
**  WallSpace(char symbol, ANSIColor color) constructor
**	Description:  Initialize WallSpace object
*********************************************************************/
WallSpace::WallSpace(char symbol, ANSIColor color, ANSIColor backColor)
{
	setTraversable(false);
	setSymbol(symbol);
	setColor(color);
	setBackColor(backColor);
}


/********************************************************************
**  WallSpace *create() override
**	Description:  Overridden create - allows clone
*********************************************************************/
WallSpace* WallSpace::create()
{
	return new WallSpace;
}

/********************************************************************
**  WallSpace *clone() override
**	Description:  Allows clone into Space*
*********************************************************************/
WallSpace* WallSpace::clone()
{
	WallSpace *clone = new WallSpace();

	clone->setSymbol(this->getSymbol());
	clone->setColor(this->getColor());
	clone->setBackColor(this->getBackColor());
	clone->setTraversable(this->getTraversable());

	return clone;
}


/********************************************************************
**  virtual void checkForEvent() override
**	Description:  Emits events
*********************************************************************/
void WallSpace::checkForEvent()
{

}