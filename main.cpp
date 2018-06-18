/*********************************************************************
** Program name:  Snake (Final Project)
** Author:  Matt Britt
** Date:  12/3/17
** Description:  Snake game played via terminal on FLIP
**
**  Features:
**	1. Event system allowing modules to communicate and track game events
**			- allows multiple events (ex: update time, update move, etc) at once
**
**	2. Screen class only outputs changes in order to conserve bandwidth
**			- ideal stolen from React.js state management
**			- snake movement only modifies three cells
**
**	3. Levels can be loaded from text files
**
**	4. Control class reads keys w/o needing newline
**
*********************************************************************/


#include <iostream>
#include <string>
#include <fstream>

#include "Game.hpp"
#include "Control.hpp"
#include "ANSI_Menu.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

string levelMenu();									// menu to choose level
void outcomeScreen(bool won);						// displays outcome of game
void terminalWarning();								// displays terminal message at start (not as dire as it sounds!)


int main()
{

	// display terminal message
	terminalWarning();
	
	// setup menu
	vector<string> menuOptions{
		"Play First Level",
		"Select Level",
		"Exit"
	};

	ANSI_Menu menu(menuOptions);

	
	string nextLevel;
	int choice = 0;

	// loop menu until user selects exit
	while (choice < 3)								// 4 is choice for exit
	{
		choice = menu.displayMenu("WELCOME TO SNAKE");
	
		
		switch (choice)
		{
			case 1:					// play 1st/next level 
			{
				// play the next level of the game
				Game game;
				game.play(nextLevel);

				// set next level based on if game was won or not
				if (game.gameWon())
				{
					nextLevel = game.getNextLevel();
				}

				// display outcome
				outcomeScreen(game.gameWon());
			}
				break;
		
			case 2:					// select level (from built in levels)
			{

				// get level filename
				string levelName = levelMenu();

				// if no level selected, break
				if (levelName == "")
				{
					continue;
					//break;
				}

				// otherwise play selected level
				Game game;
				game.play(levelName);
				
				// if won, set nextLevel
				if (game.gameWon())
				{
					nextLevel = game.getNextLevel();
				}
				
				// display outcome
				outcomeScreen(game.gameWon());
			}
				break;
		}
			

		// update menu after first run
		menuOptions[0] = "Play Next Level";
		menu.loadOptions(menuOptions);
	}

	cout << endl << endl;
	cout << "Thanks For Playing Snake" << endl << endl;


	return 0;
}


/********************************************************************
**  void outcomeScreen(bool won)
**	Description:  Displays outcome of game
*********************************************************************/
void outcomeScreen(bool won)
{
	cout << CLEAR_SCREEN << CLEAR_COLOR;

	cout << ANSI_AbsolutePositionToCode(2, 10);

	if (won)
	{
		cout << "YOU WON!   CONGRATULATIONS";
	}
	else
	{
		cout << "Unfortunately you didn't win this one, maybe next time . . .";
	}

	cout << ANSI_AbsolutePositionToCode(4, 10);
	cout << "Press Enter to continue";

	cout << CURSOR_HOME << CLEAR_LINE;

	// ensure that user input doesn't skip this screen
	system("stty cooked");
	string throwAway;
	getline(cin, throwAway);
	system("stty raw");
}


/********************************************************************
**  string levelMenu
**	Description:  Menu to choose level, returns file name
*********************************************************************/
string levelMenu()
{
	ifstream inFile("levels.txt");
	vector<string> levelOptions;

	// if file is valid, load filenames into vector
	if (inFile)
	{
		string line;

		while (getline(inFile, line))
		{
			levelOptions.push_back(line);
		}
	}
	// else file not vaild, display message and abort
	else 
	{
		cout << endl << endl;
		cout << "levels.txt failed to load" << endl;
		cout << "Press Enter to continue";
		cin.get();
		cout << endl << endl;
		return "";
	}
	
	// add cancel option
	levelOptions.push_back("Cancel");

	ANSI_Menu menu(levelOptions);

	int choice = menu.displayMenu("Choose a level");

	// cancel choice, abort
	if (choice == levelOptions.size())
	{
		return "";
	}
	
	// return select filename
	return levelOptions[choice - 1];
}

/********************************************************************
**  void terminalWarning()
**	Description:  Displays message about terminals at start
*********************************************************************/
void terminalWarning()
{
	cout << CLEAR_SCREEN;

	cout << "This program uses ANSI control codes that may not " << endl;
	cout << "be properly handled by some terminal programs." << endl;
	
	cout << "This was tested on Putty v 0.68 with default settings," << endl;
	cout << "including a 80 column, 24 row display." << endl << endl;

	cout << "Press Enter to start.  Enjoy!";

	// ensure that user input doesn't skip this screen
	system("stty cooked");
	string throwAway;
	getline(cin, throwAway);
	system("stty raw");
}
