/**********************************************************************
**	ANSI_Menu.hpp
**	Author: Matt Britt
**	Date: 12/4/2017
**	Description:   ANSI_Menu.hpp is the header file for the ANSI_Menu class.
**				The ANSI_Menu class is a menu system
*********************************************************************/

#ifndef ANSI_MENU_HPP
#define ANSI_MENU_HPP

#include <vector>
#include <string>
#include <iostream>

#include "ANSI_Codes.hpp"
#include "Control.hpp"

using std::vector;
using std::string;
using std::cout;

class ANSI_Menu
{
private:
	Control ctrl;											// control object for keyboard input
	
	vector<string> menuOptions;								// vector with menu options

	int option = 1;											// selected option
	string prompt;											// prompt to display at top

public:
	ANSI_Menu();											// default constructor
	ANSI_Menu(vector<string> &options);						// constructor allows loading of options

	void loadOptions(vector<string> &menuOptions);			// load menu options
	int displayMenu(string prompt);							// display menu and return choice selected

	void updateScreen();									// outputs menu to display, highlights option
	int handleKey(Key key);									// handles key input, returns selection
};

#endif

