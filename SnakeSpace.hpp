/**********************************************************************
**	SnakeSpace.hpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   SnakeSpace.hpp is the header file for the SnakeSpace class.
**				The SnakeSpace class represents the snake segment in SpaceGrid.
**				SnakeSpace inherits the Space class.
*********************************************************************/

#ifndef SNAKESPACE_HPP
#define SNAKESPACE_HPP

#include "Space.hpp"


class SnakeSpace : public Space
{
private:

public:
	// constructor
	SnakeSpace(char symbol, ANSIColor color, ANSIColor backColor);
	SnakeSpace();											// default constructor

	// overridden virtual function
	SnakeSpace* create() override;							// overridden create
	SnakeSpace* clone() override;							// overridden clone

	virtual void checkForEvent() override;					// emits events
};


#endif
