/**********************************************************************
**	PointSpace.hpp
**	Author: Matt Britt
**	Date: 12/3/2017
**	Description:   PointSpace.hpp is the header file for the PointSpace class.
**				The PointSpace class represents of point that enlarges your snake.
**				The PointSpace class inherits the Space class.
*********************************************************************/

#ifndef POINTSPACE_HPP
#define POINTSPACE_HPP

#include "Space.hpp"

class PointSpace : public Space
{
private:


public:
	PointSpace(char symbol, ANSIColor color, ANSIColor backColor);				// constructor
	PointSpace();											// default constructor

	virtual void checkForEvent() override;					// emits events	
	virtual PointSpace* create() override;					// overridden create
	virtual PointSpace* clone() override;					// overridden clone

};

#endif


