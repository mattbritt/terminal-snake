/**********************************************************************
**	Screen.hpp
**	Author: Matt Britt
**	Date: 11/30/2017
**	Description:   Screen.hpp is the header file for the Screen class.
**				The Screen class loads and draws the screen.
*********************************************************************/

#include "Screen.hpp"

/********************************************************************
**  Screen() constructor
**	Description:  Initialize Screen object
*********************************************************************/
Screen::Screen()
{

}

/********************************************************************
**  void update()
**	Description:  Redraws Screen
*********************************************************************/
void Screen::updateGrid(SpaceGridR &grid)
{
	vector<string> updateVector;

	// get updated strings to display for grid
	grid.getUpdate(updateVector);

	for (auto element : updateVector)
	{
		cout << element;
	}

	cout << ANSI_ColorToCodeForeGround(BLACK) << CURSOR_HOME;
}

/********************************************************************
**  void updateTitleBar()
**	Description:  Updates bar at top of screen
*********************************************************************/
void Screen::updateTitleBar(int score, int lives, int time)
{
	cout << CLEAR_COLOR;

	// check if we need to update
	if (score == lastScore && lives == lastLives && time == lastTime)
	{
		return;
	}

	// set colors
	cout << SET_BOLD << ANSI_ColorToCodeBackGround(WHITE);
	cout << ANSI_ColorToCodeForeGround(BLACK);

	// update score if needed
	if (score != lastScore)
	{
		cout << SCORE_POSITION << "SCORE: " << std::right << std::setw(5) << to_string(score);
		lastScore = score;
	}
	
	// update lives if needed
	if (lives != lastLives)
	{
		cout << LIVES_POSITION << "LIVES: " << std::right << std::setw(4) << to_string(lives);
		lastLives = lives;
	}

	// update time if needed
	if (time != lastTime)
	{
		cout << TIME_POSITION << "TIME: " << std::right << std::setw(4) << to_string(time);
		lastTime = time;
	}
	cout << CLEAR_COLOR;
}