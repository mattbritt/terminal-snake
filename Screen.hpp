/**********************************************************************
**	Screen.hpp
**	Author: Matt Britt
**	Date: 11/30/2017
**	Description:   Screen.hpp is the header file for the Screen class.
**				The Screen class loads and draws the screen.
*********************************************************************/

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <string>
#include <iomanip>

#include "SpaceGrid.hpp"
#include "Snake.hpp"
#include "EventObj.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Screen
{
private:
	// Constants:
	// ANSI Terminal Commands:
	string CURSOR_HOME = "\033[23;1H";				// cursor home position (where key entry happens)
	string CLEAR_LINE = "\033[2K";					// clears entire line							
	string CLEAR_SCREEN = "\033[2J";				// clears entire screen

	string SCORE_POSITION = "\033[1;1H";			// position for score
	string LIVES_POSITION = "\033[1;35H";			// position for lives counter
	string TIME_POSITION = "\033[1;65H";			// position for time countdown

	// Variables:
	EventObj eventObj;								// used to pass events

	long lastScore = -1;							// tracks changes in score
	int lastLives = -1;								// tracks changes in lives
	int lastTime = -1;								// tracks changes in time

public:

	Screen();										// constructor

	void updateGrid(SpaceGridR &grid);						// updates screen using grid info
	void updateTitleBar(int score, int lives, int time);	// updates the bar at the top of screen

};


#endif
