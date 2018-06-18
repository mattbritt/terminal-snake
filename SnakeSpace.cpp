/**********************************************************************
**	SnakeSpace.cpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   SnakeSpace.cpp is the implementation file for the SnakeSpace class.
**				The SnakeSpace class represents the snake segment in SpaceGrid.
**				SnakeSpace inherits the Space class.
*********************************************************************/

#include "SnakeSpace.hpp"

/********************************************************************
**  SnakeSpace() default constructor
**	Description:  Initialize SnakeSpace object
*********************************************************************/
SnakeSpace::SnakeSpace()
{

}


/********************************************************************
**  SnakeSpace() constructor
**	Description:  Initialize SnakeSpace object
*********************************************************************/
SnakeSpace::SnakeSpace(char symbol, ANSIColor color, ANSIColor backColor)
{
	setTraversable(false);
	setSymbol(symbol);
	setColor(color);
	setBackColor(backColor);
}


/********************************************************************
**  SnakeSpace *create() override
**	Description:  Overridden create - allows clone
*********************************************************************/
SnakeSpace* SnakeSpace::create()
{
	return new SnakeSpace;
}

/********************************************************************
**  SnakeSpace *clone() override
**	Description:  Allows clone into Space*
*********************************************************************/
SnakeSpace* SnakeSpace::clone()
{
	SnakeSpace *clone = new SnakeSpace();

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
void SnakeSpace::checkForEvent()
{

}