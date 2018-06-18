/**********************************************************************
**	ANSI_Menu.cpp
**	Author: Matt Britt
**	Date: 12/4/2017
**	Description:   ANSI_Menu.cpp is the implementation file for the ANSI_Menu class.
**				The ANSI_Menu class is a menu system
*********************************************************************/

#include "ANSI_Menu.hpp"

/********************************************************************
**  ANSI_Menu()
**	Description:  Default constructor
*********************************************************************/
ANSI_Menu::ANSI_Menu()
{

}

/********************************************************************
**  ANSI_Menu(vector<string> menuOptions)
**	Description:  Constructor allows loading of option
*********************************************************************/
ANSI_Menu::ANSI_Menu(vector<string> &options)
{
	loadOptions(options);
}

/********************************************************************
**  loadOptions(vector<string> menuOptions)
**	Description:  Loads options
*********************************************************************/
void ANSI_Menu::loadOptions(vector<string> &menuOptions)
{
	this->menuOptions = menuOptions;
}

/********************************************************************
**  int displayMenu()
**	Description:  Displays menu and returns choice selected
*********************************************************************/
int ANSI_Menu::displayMenu(string prompt)
{
	this->prompt = prompt;

	Key loopKey = NO_KEY;

	// main game loop (until quit key 'q' is pressed)
	while (loopKey != ENTER_KEY)
	{
		// update screen
		updateScreen();

		// poll keyboard; this is what introduces the main delay needed 
		loopKey = ctrl.pollKey(150);

		// if we got a key, do something with it
		if (loopKey != NO_KEY && loopKey != QUIT_KEY)
		{
			handleKey(loopKey);
		}
	}

	return option;
}

/********************************************************************
**  void updateScreen(int highlightOption)
**	Description:  Outputs menu to screen, highlights option
*********************************************************************/
void ANSI_Menu::updateScreen()
{
	cout << CLEAR_SCREEN << CURSOR_HOME;

	// display prompt
	cout << ANSI_AbsolutePositionToCode(2, 10);
	cout << ANSI_ColorToCodeForeGround(BLACK) <<  ANSI_ColorToCodeBackGround(WHITE);
	cout << " " << prompt << " ";
	cout << CLEAR_COLOR;
	
	// display instruction string
	cout << ANSI_AbsolutePositionToCode(4, 10);
	cout << ANSI_ColorToCodeForeGround(WHITE);
	cout << "Use UP and DOWN arrows to choose options, ENTER to select";
	cout << CLEAR_COLOR;

	// display options, highlight current selection
	for (int i = 0; i < menuOptions.size(); i++)
	{
		cout << ANSI_ColorToCodeForeGround(WHITE);
		if (i == option - 1)
		{
			cout << ANSI_ColorToCodeForeGround(BLACK) << ANSI_ColorToCodeBackGround(WHITE);
		}
	
		cout << ANSI_AbsolutePositionToCode(i + 6, 10);

		cout << menuOptions[i];
		cout << CLEAR_COLOR;
	}
}


/********************************************************************
**  int handleKey(Key key)
**	Description:  Handles key input, returns selection
*********************************************************************/
int ANSI_Menu::handleKey(Key key)
{
	switch (key)
	{
	case UP_KEY:
		if (option > 1)
		{
			option--;
		}
		break;

	case DOWN_KEY:
		if (option < menuOptions.size())
		{
			option++;
		}
		
	}
}


