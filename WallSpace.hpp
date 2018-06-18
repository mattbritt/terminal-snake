/**********************************************************************
**	WallSpace.hpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   WallSpace.hpp is the header file for the WallSpace class.
**				The WallSpace class represents an empty (that is not traversable)
**				Space object.  WallSpace inherits the Space class.
*********************************************************************/

#ifndef WALLSPACE_HPP
#define WALLSPACE_HPP

#include "Space.hpp"

class WallSpace : public Space
{
private:


public:
	WallSpace();										// default constructor
	WallSpace(char symbol, ANSIColor color, ANSIColor backColor);			// constructor

	virtual void checkForEvent() override;				// emits event
	virtual WallSpace* create() override;				// overridden create
	virtual WallSpace* clone() override;				// overridden clone

};


#endif