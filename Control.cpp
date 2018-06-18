/**********************************************************************
**	Control.cpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   Control.cpp is the implementation file for the Control class.
**				The Control class polls for and gets input from keyboard.
*********************************************************************/

#include "Control.hpp"

/********************************************************************
**  Key pollKey(int ms)
**	Description:  Polls for input for ms milliseconds, returns Key pressed
*********************************************************************/
Key Control::pollKey(int ms)
{
	// based on original terminal control code in Terry Quest by Harlan James
	system("stty raw");

	bool gotKey = false;

	pollfd fd;

	clock_t stopTime = ((double)ms / 1000.0) * CLOCKS_PER_SEC ;   // calc stopTime in clocks; reduces overhead in timing loop below
	stopTime += eventObj.updateTime();				// sets stopTime to currentTime + ms & updates timer (EventObj)
	
	cout << CURSOR_HOME << CLEAR_LINE << endl;			// critical endl

	do
	{
		// poll code courtesy of https://stackoverflow.com/questions/4656388/poll-stdin-and-other-fds
		fd.fd = 0;
		fd.events = POLLIN;
		fd.revents = 0;

		int ret = poll(&fd, 1, 0);
		
		// if there's a key available, exit loop
		if (ret > 0 && (fd.revents & POLLIN != 0))
		{
			gotKey = true;
			cout << CLEAR_LINE;
		}

	} while (!gotKey && (clock() < stopTime));

	// reset cursor line
	cout << CURSOR_HOME << CLEAR_LINE;


	// if we polled a key
	if (gotKey)
	{
		char key;
		Key retKey = NO_KEY;

		// we can extract now extract a key from stdin w/o blocking
		key = cin.get();

		if (key == 27)					// handle escape sequence on arrow keys
		{
			key = cin.get();
			key = cin.get();			// discard extraneous chars
		}

		// parse key code
		switch (key)
		{
		case 13:
			retKey = ENTER_KEY;
			break;

		case 65:
			retKey = UP_KEY;
			break;

		case 66:
			retKey = DOWN_KEY;
			break;

		case 67:
			retKey = RIGHT_KEY;
			break;

		case 68:
			retKey = LEFT_KEY;
			break;
		}


		// handle redefinable keys
		if (key == quitKey)
		{
			retKey = QUIT_KEY;
		}
		
		return retKey;
	}

	// else loop timeout == no key pressed
	else
	{
		return NO_KEY;
	}
}

/********************************************************************
**  Direction keyToDir(Key key)
**	Description:  Convert Key to Direction
*********************************************************************/
Direction Control::keyToDir(Key key)
{
	switch (key)
	{
	case UP_KEY:
		return UP;
		break;

	case DOWN_KEY:
		return DOWN;
		break;

	case LEFT_KEY:
		return LEFT;
		break;

	case RIGHT_KEY:
		return RIGHT;
		break;
	}
}
