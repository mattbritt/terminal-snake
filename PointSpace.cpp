/**********************************************************************
**	PointSpace.cpp
**	Author: Matt Britt
**	Date: 12/3/2017
**	Description:   PointSpace.cpp is the implementation file for the PointSpace class.
**				The PointSpace class represents of point that enlarges your snake.
**				The PointSpace class inherits the Space class.
*********************************************************************/

#include "PointSpace.hpp"

/********************************************************************
**  PointSpace() default constructor
**	Description:  Initialize PointSpace object
*********************************************************************/
PointSpace::PointSpace()
{

}

/********************************************************************
**  PointSpace() constructor
**	Description:  Initialize PointSpace object
*********************************************************************/
PointSpace::PointSpace(char symbol, ANSIColor color, ANSIColor backColor)
{
	setTraversable(true);
	setSymbol(symbol);
	setColor(color);
	setBackColor(backColor);

}

/********************************************************************
**  PointSpace *create() override
**	Description:  Overridden create - allows clone
*********************************************************************/
PointSpace* PointSpace::create()
{
	return new PointSpace;
}

/********************************************************************
**  PointSpace *clone() override
**	Description:  Allows clone into Space*
*********************************************************************/
PointSpace* PointSpace::clone()
{
	PointSpace *clone = new PointSpace();

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
void PointSpace::checkForEvent()
{
	int extendCount = symbol - 48;   // get number from symbol - ascii code for 0

	// add extendCount snake segments / EXTEND events
	for (int i = 0; i < extendCount; i++)
	{
		eventObj.addEvent("", EXTEND);
	}

	// emit Point event
	eventObj.addEvent("", POINT);
}



