/**********************************************************************
**	EmptySpace.hpp
**	Author: Matt Britt
**	Date: 11/30/2017
**	Description:   EmptySpace.hpp is the header file for the EmptySpace class.
**				The EmptySpace class represents an empty (that is traversable)
**				Space object.  EmptySpace inherits the Space class.
*********************************************************************/

#ifndef EMPTYSPACE_HPP
#define EMPTYSPACE_HPP

#include "Space.hpp"

class EmptySpace : public Space
{
private:

public:
	EmptySpace(char symbol, ANSIColor color, ANSIColor backColor);				// constructor
	EmptySpace();											// default constructor

	virtual void checkForEvent() override;					// emits events	
	virtual EmptySpace* create() override;					// overridden create
	virtual EmptySpace* clone() override;					// overridden clone
};


#endif