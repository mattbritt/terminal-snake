/**********************************************************************
**	EmptySpace.cpp
**	Author: Matt Britt
**	Date: 11/30/2017
**	Description:   EmptySpace.cpp is the implementation file for the EmptySpace class.
**				The EmptySpace class represents an empty (that is traversable)
**				Space object.  EmptySpace inherits the Space class.
*********************************************************************/

#include "EmptySpace.hpp"

/********************************************************************
**  EmptySpace() default constructor
**	Description:  Initialize EmptySpace object
*********************************************************************/
EmptySpace::EmptySpace()
{

}

/********************************************************************
**  EmptySpace() constructor
**	Description:  Initialize EmptySpace object
*********************************************************************/
EmptySpace::EmptySpace(char symbol, ANSIColor color, ANSIColor backColor)
{
	setTraversable(true);
	setSymbol(symbol);
	setColor(color);
	setBackColor(backColor);

}

/********************************************************************
**  EmptySpace *create() override
**	Description:  Overridden create - allows clone
*********************************************************************/
EmptySpace* EmptySpace::create()
{
	return new EmptySpace;
}

/********************************************************************
**  EmptySpace *clone() override
**	Description:  Allows clone into Space*
*********************************************************************/
EmptySpace* EmptySpace::clone()
{
	EmptySpace *clone = new EmptySpace();

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
void EmptySpace::checkForEvent()
{

}