/**********************************************************************
**	Control.hpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   Control.hpp is the header file for the Control class.
**				The Control class polls for and gets input from keyboard.
*********************************************************************/

#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <poll.h>
#include <time.h>
#include <unistd.h>

#include <iostream>

#include "ANSI_Codes.hpp"
#include "Direction.hpp"
#include "EventObj.hpp"

using std::cout;
using std::endl;
using std::cin;

enum Key { NO_KEY, LEFT_KEY, RIGHT_KEY, UP_KEY, DOWN_KEY, QUIT_KEY, ENTER_KEY };					// codes to return -- indicate key pressed

class Control
{
private:
	EventObj eventObj;
	char quitKey = 'q';											// key to exit

public:

	Key pollKey(int ms);										// polls for user input for ms milliseconds, returns keypress
	Direction keyToDir(Key key);								// convert key to direction
};


#endif

