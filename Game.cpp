/**********************************************************************
**	Game.cpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   Game.cpp is the implementation file for the Game class.
**				The Game class orchestrates the game events
*********************************************************************/

#include "Game.hpp"

/********************************************************************
**  Game()
**	Description:  Constructor, initializes Game object
*********************************************************************/
Game::Game()
{

}

/********************************************************************
**  ~Game()
**	Description:  Destructor
*********************************************************************/
Game::~Game()
{
	// delete snake
	if (snake != nullptr)
	{
		delete snake;
		snake = nullptr;
	}

	system("stty cooked");			// restore normal tty function
}

/********************************************************************
**  bool loadLevel(string fileName)
**	Description:  Load level
*********************************************************************/
bool Game::loadLevel(string fileName)
{
	// load level
	grid.loadGrid(fileName);

	// get levelInfo
	parseLevelInfo();

	// delete any previous snakes
	if (snake != nullptr)
	{
		delete snake;
		snake = nullptr;
	}

	// add snake
	snake = new Snake(levelInfo.snakeRow, levelInfo.snakeCol, grid);
}

/********************************************************************
**  void gameLoop()
**	Description:  Main execution loop for game
*********************************************************************/
void Game::gameLoop()
{
	cout << CLEAR_SCREEN;

	// init eventObj timer
	eventObj.resetTimer();
	eventObj.clearEvents();

	// add first point space
	addRandomPoint();


	Key loopKey = NO_KEY;

	// main game loop (until quit key 'q' is pressed)
	while (loopKey != QUIT_KEY)
	{
		// check for gameOver; if true end level
		if (gameOver)
		{
			break;
		}

		// check for new events
		handleEvents();

		// move snake forward one space
		snake->moveForward();
	
		// draw screen grid and title bar
		scr.updateGrid(grid);
		scr.updateTitleBar(score, lives, time);

		// poll keyboard; this is what introduces the main delay needed 
		loopKey = ctrl.pollKey(delay);

		// if we got a key, do something with it
		if (loopKey != NO_KEY && loopKey != QUIT_KEY)
		{
			handleKey(loopKey);
		}
	}

}

/********************************************************************
**  void handleKey(Key key)
**	Description:  Handles key press events
*********************************************************************/
void Game::handleKey(Key key)
{
	switch (key)
	{
	case UP_KEY:

	case DOWN_KEY:

	case RIGHT_KEY:

	case LEFT_KEY:
		snake->moveSnake(ctrl.keyToDir(key));
		break;
	}
}


/********************************************************************
**  void updateTime()
**	Description:  Updates time
*********************************************************************/
void Game::updateTime()
{
	time--;

	// if we're out of time, game is lost and gameOver flag set to true
	if (time <= 0)
	{
		eventObj.addEvent("", LOST);
		gameOver = true;
	}
}

/********************************************************************
**  void handleEvents()
**	Description:  Watch for and handle events
*********************************************************************/
void Game::handleEvents()
{
	// update game time if SECOND event exists
	if (eventObj.eventIndex(SECOND) > -1)
	{
		updateTime();
	}

	// update score, add new point, increase speed
	if (eventObj.eventIndex(POINT) > -1)
	{
		handlePointEvent();
	}

	// handle COLLIDE
	if(eventObj.eventIndex(COLLIDE) > -1)
	{
		handleCollideEvent();
	}

	
}


/********************************************************************
**  void handleCollideEvent()
**	Description:  Decrement lives, check for game over
*********************************************************************/
void Game::handleCollideEvent()
{
	// decrement lives
	lives--;

	if (lives <= 0)
	{
		eventObj.addEvent("", LOST);
		gameOver = true;
	}
}



/********************************************************************
**  void handlePointEvent
**	Description:  Updates score, adds new random point, increases speed
*********************************************************************/
void Game::handlePointEvent()
{
	// clear POINT events
	eventObj.clearEvent(POINT);

	// update score
	score += pointVal * (time / 10);

	// check if level won / final point (#9)
	if(pointVal >= 9)
	{ 
		// emit WON event
		eventObj.addEvent("", WON);

		// set gameOver to end level
		gameOver = true;

		return;
	}

	// add new random point to grid
	addRandomPoint();

	// increase speed
	delay = delay - (delay * (DELAY_DECREASE / 100.0));
}


/********************************************************************
**  void addPoint(int row, int col)
**	Description:  adds next point at given index
*********************************************************************/
void Game::addPoint(int row, int col)
{
	// increment pointVal
	pointVal++;

	// create new PointSpace with char == point value
	Space* pointPtr = new PointSpace(pointVal + 48, BLUE, GREEN);

	// add new PointSpace to grid
	grid.addSpace(row, col, pointPtr);

}

/********************************************************************
**  void addRandomPoint(int row, int col)
**	Description:  adds point randomly in play area
*********************************************************************/
void Game::addRandomPoint()
{
	// init rng
	// <Random> code from https://docs.microsoft.com/en-us/cpp/standard-library/random
	std::random_device rd;
	std::mt19937 gen(rd());
	
	std::uniform_int_distribution<int> rowDist(0, grid.getRows() - 1);		// random row number
	std::uniform_int_distribution<int> colDist(0, grid.getCols() - 1);		// random col number

	bool validSpaceBool = false;
	
	Space *ptr = nullptr;

	int row;
	int col;

	while (!validSpaceBool)
	{
		// get random row and col
		row = rowDist(rd);
		col = colDist(rd);

		ptr = grid.getSpace(row, col);

		// if we have a valid space, exit loop
		if (ptr && ptr->getTraversable())
		{
			validSpaceBool = true;
		}
	}

	addPoint(row, col);

}

/********************************************************************
**  void parseLevel()
**	Description:  Parses levelInfo into variables
*********************************************************************/
void Game::parseLevelInfo()
{
	// get level info
	levelInfo = grid.getLevelInfo();

	if (levelInfo.lives > 0)
	{
		lives = levelInfo.lives;
	}

	if (levelInfo.time > 0)
	{
		time = levelInfo.time;
	}

}

/********************************************************************
**  void play()
**	Description:  Load and play level
*********************************************************************/
void Game::play(string fileName)
{
	if (fileName == "")
	{
		loadLevel("0.txt");
	}
	else
	{
		loadLevel(fileName);
	}

	// show instructions, then play game
	instructionScreen();
	gameLoop();
}

/********************************************************************
**  string getNextLevel()
**	Description:  Getter, returns nextLevel
*********************************************************************/
string Game::getNextLevel()
{
	return levelInfo.nextLevel;
}

/********************************************************************
**  bool gameWon()
**	Description:  Returns true if game was won (if WON event exists)
*********************************************************************/
bool Game::gameWon()
{
	if (eventObj.eventIndex(WON) > -1)
	{
		return true;
	}

	return false;
}

/********************************************************************
**  void instructionScreen()
**	Description:  Displays instructions
*********************************************************************/
void Game::instructionScreen()
{
	cout << CLEAR_SCREEN << CLEAR_COLOR;

	cout << ANSI_ColorToCodeForeGround(BLUE);
	cout << ANSI_ColorToCodeBackGround(WHITE);

	cout << ANSI_AbsolutePositionToCode(2, 10);

	cout << "INSTRUCTIONS";

	cout << CLEAR_COLOR;

	cout << ANSI_AbsolutePositionToCode(4, 10);
	cout << "Move snake with arrow keys (UP, DOWN, LEFT, RIGHT)";
	cout << ANSI_AbsolutePositionToCode(6, 10);
	cout << "The goal is to eat the numbers that appear on screen";
	cout << ANSI_AbsolutePositionToCode(8, 10);
	cout << "Eating all 9 numbers will win the game";
	cout << ANSI_AbsolutePositionToCode(10, 10);
	cout << "Avoid walls, obstacles and your own snake's body";
	cout << ANSI_AbsolutePositionToCode(12, 10);
	cout << "Colliding with an object will deduct a life";
	cout << ANSI_AbsolutePositionToCode(14, 10);
	cout << "If time runs out, the game will be over";
	cout << ANSI_AbsolutePositionToCode(16, 10);
	cout << "Pressing q will quit level";
	cout << ANSI_AbsolutePositionToCode(18, 10);
	cout << "Press Enter to start";


	cout << CURSOR_HOME << CLEAR_LINE;
	cin.get();
}