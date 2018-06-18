/**********************************************************************
**	Game.hpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   Game.hpp is the header file for the Game class.
**				The Game class orchestrates the game events
*********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include <random>

#include "Screen.hpp"
#include "Control.hpp"
#include "SpaceGrid.hpp"
#include "Snake.hpp"
#include "EventObj.hpp"

class Game
{
private:

	// constants:
	const int DEFAULT_DELAY = 200;					// default delay in milliseconds
	const float DELAY_DECREASE = 20.0;				// % faster each point
	
	const int DEFAULT_TIME = 120;					// default seconds	
	const int DEFAULT_LIVES = 2;					// default # of lives



	// variables:
	int time = DEFAULT_TIME;						// game time
	long score = 0;									// score
	int lives = DEFAULT_LIVES;						// player lives

	LevelInfo levelInfo;							// level info struct

	bool gameOver = false;							// flag set when game is complete

	int delay = DEFAULT_DELAY;						// delay (lower == faster snake)

	int pointVal = 0;								// value of current PointSpace

	Control ctrl;									// control object, get keyboard input
	SpaceGridR grid;								// grid representing play area
	Screen scr;										// screen object, draws screen

	EventObj eventObj;								// event object, communicates events

	Snake *snake = nullptr;// = Snake(-1, -1, grid);				// player's snake

public:
	Game();											// constructor
	~Game();										// destructor

	void gameLoop();								// main execution loop of game
	void handleKey(Key key);						// handles key press events

	void updateTime();								// updates time

	void handleEvents();							// watches for various events
	
	void addRandomPoint();							// adds point randomly in play area
	void addPoint(int row, int col);				// adds next point at given index

	void handlePointEvent();						// update score, adds new random point, increase speed
	void handleCollideEvent();						// decrement lives, check for game over

	void parseLevelInfo();							// parses levelInfo into variables

	bool loadLevel(string fileName);				// load level

	void play(string fileName = "");				// load and play next level

	bool gameWon();									// returns true if game was won

	string getNextLevel();							// getter, returns next level

	void instructionScreen();						// displays instructions
};

#endif
